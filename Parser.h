#pragma once

#include "AbstractFilter.h"

#include <filesystem>

namespace cli {

void PrintInfo();

class Parser {
public:
    Parser(int arg_count, char** arg_value);

    void GetFilters(std::vector<std::unique_ptr<image_processor::AbstractFilter>>& filters) const;

    std::filesystem::path GetInputPath() const;

    std::filesystem::path GetOutputPath() const;

    bool AnyParsed() const;

private:
    bool filters_parsed_ = false;
    std::filesystem::path input_path_;
    std::filesystem::path output_path_;
    std::vector<std::pair<std::string_view, std::vector<std::string_view>>> filter_args_;
};
}  // namespace cli