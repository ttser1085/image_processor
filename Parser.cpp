#include "Parser.h"

#include "CropFilter.h"
#include "GrayscaleFilter.h"
#include "NegativeFilter.h"
#include "SharpeningFilter.h"
#include "EdgeFilter.h"
#include "GaussianBlurFilter.h"
#include "CrystallizeFilter.h"

#include <iostream>

namespace {

bool IsUnsignedInteger(std::string_view str) {
    if (str.empty()) {
        return false;
    }

    return std::all_of(str.begin(), str.end(), [](char c) { return std::isdigit(c); });
}

bool IsUnsignedDouble(std::string_view str) {
    if (str.empty()) {
        return false;
    }

    return std::all_of(str.begin(), str.end(), [](char c) { return std::isdigit(c) || c == '.'; }) &&
           std::count(str.begin(), str.end(), '.') <= 1 && str[0] != '.';
}

bool IsInteger(std::string_view str) {
    if (str.empty()) {
        return false;
    }

    return IsUnsignedInteger(str) || (str[0] == '-' && IsUnsignedInteger(std::string_view(str.begin() + 1, str.end())));
}

bool IsDouble(std::string_view str) {
    if (str.empty()) {
        return false;
    }

    return IsUnsignedDouble(str) || (str[0] == '-' && IsUnsignedDouble(std::string_view(str.begin() + 1, str.end())));
}

void CheckPaths(const std::filesystem::path &input, const std::filesystem::path &output) {
    if (!std::filesystem::exists(input)) {
        throw std::invalid_argument("File not exist: " + input.string());
    }

    if (!std::filesystem::exists(output.parent_path())) {
        throw std::invalid_argument("Path not exist: " + output.parent_path().string());
    }
}

}  // namespace

void cli::PrintInfo() {
    std::cout << "Image Processor - simple image filter engine" << std::endl;
    std::cout << "supported formats: .bmp" << std::endl;
    std::cout << "format of input: ./image_processor {input file path} {output file formats} "
                 "[-{filter name 1} [filter argument 1] [filter argument 2] ...] [-{filter name 2} [filter argument "
                 "1] [filter argument 2] ...] ..."
              << std::endl;
    std::cout << "Supported filters:" << std::endl;
    std::cout << "\tCrop (-crop width height)" << std::endl;
    std::cout << "\tGrayscale (-gs)" << std::endl;
    std::cout << "\tNegative (-neg)" << std::endl;
    std::cout << "\tSharpening (-sharp)" << std::endl;
    std::cout << "\tEdge Detection (-edge threshold)" << std::endl;
    std::cout << "\tGaussian Blur (-blur sigma)" << std::endl;
    std::cout << "\tCrystallize (-crystal amount)" << std::endl;
}

cli::Parser::Parser(int arg_count, char **arg_value) {
    if (arg_count == 1) {
        filters_parsed_ = false;
        return;
    } else if (arg_count == 2) {
        throw std::invalid_argument("Illegal number of arguments");
    }

    input_path_ = std::filesystem::path(arg_value[1]);
    output_path_ = std::filesystem::path(arg_value[2]);

    CheckPaths(input_path_, output_path_);

    for (int i = 3; i < arg_count; ++i) {
        if (arg_value[i][0] == '-') {
            if (!filter_args_.empty() &&
                (IsInteger(std::string_view(arg_value[i])) || IsDouble(std::string_view(arg_value[i])))) {
                filter_args_.back().second.push_back(arg_value[i]);
            } else {
                filter_args_.push_back({std::string_view(arg_value[i]), std::vector<std::string_view>()});
            }
        } else {
            filter_args_.back().second.push_back(arg_value[i]);
        }
    }

    filters_parsed_ = true;
}

void cli::Parser::GetFilters(std::vector<std::unique_ptr<image_processor::AbstractFilter>> &filters) const {
    filters.clear();
    for (const auto &[filter_name, filter_args] : filter_args_) {
        if (filter_name == "-crop") {
            if (filter_args.size() != 2) {
                throw std::invalid_argument("Illegal number of arguments for crop filter");
            }

            if (!IsUnsignedInteger(filter_args[0])) {
                throw std::invalid_argument("Illegal argument: " + std::string(filter_args[0]));
            }
            if (!IsUnsignedInteger(filter_args[1])) {
                throw std::invalid_argument("Illegal argument: " + std::string(filter_args[1]));
            }

            filters.push_back(std::make_unique<image_processor::CropFilter>(std::stol(filter_args[0].data()),
                                                                            std::stol(filter_args[1].data())));
        } else if (filter_name == "-gs") {
            if (!filter_args.empty()) {
                throw std::invalid_argument("Illegal number of arguments for grayscale filter");
            }

            filters.push_back(std::make_unique<image_processor::GrayscaleFilter>());
        } else if (filter_name == "-neg") {
            if (!filter_args.empty()) {
                throw std::invalid_argument("Illegal number of arguments for negative filter");
            }

            filters.push_back(std::make_unique<image_processor::NegativeFilter>());
        } else if (filter_name == "-sharp") {
            if (!filter_args.empty()) {
                throw std::invalid_argument("Illegal number of arguments for sharpening filter");
            }

            filters.push_back(std::make_unique<image_processor::SharpeningFilter>());
        } else if (filter_name == "-edge") {
            if (filter_args.size() != 1) {
                throw std::invalid_argument("Illegal number of arguments for edge detection filter");
            }

            if (!IsUnsignedDouble(filter_args[0])) {
                throw std::invalid_argument("Illegal argument: " + std::string(filter_args[0]));
            }

            auto threshold = std::stod(filter_args[0].data());

            filters.push_back(std::make_unique<image_processor::EdgeFilter>(threshold));
        } else if (filter_name == "-blur") {
            if (filter_args.size() != 1) {
                throw std::invalid_argument("Illegal number of arguments for Gaussian blur filter");
            }

            if (!IsUnsignedDouble(filter_args[0])) {
                throw std::invalid_argument("Illegal argument: " + std::string(filter_args[0]));
            }

            filters.push_back(std::make_unique<image_processor::GaussianBlurFilter>(std::stod(filter_args[0].data())));
        } else if (filter_name == "-crystal") {
            if (filter_args.size() != 1) {
                throw std::invalid_argument("Illegal number of arguments for crystallize filter");
            }

            if (!IsUnsignedInteger(filter_args[0])) {
                throw std::invalid_argument("Illegal argument: " + std::string(filter_args[0]));
            }

            filters.push_back(std::make_unique<image_processor::CrystallizeFilter>(std::stol(filter_args[0].data())));
        } else {
            throw std::invalid_argument("Illegal filter: " + std::string(filter_name));
        }
    }
}

std::filesystem::path cli::Parser::GetInputPath() const {
    return input_path_;
}

std::filesystem::path cli::Parser::GetOutputPath() const {
    return output_path_;
}

bool cli::Parser::AnyParsed() const {
    return filters_parsed_;
}
