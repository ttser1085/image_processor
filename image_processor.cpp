#include "BMPHandler.h"

#include "Parser.h"
#include "CompositeFilter.h"

#include <iostream>

int main(int argc, char** argv) {
    try {
        cli::Parser parser(argc, argv);
        if (parser.AnyParsed()) {
            image_processor::Image img;
            image_processor::BMPHandler::OpenFile(parser.GetInputPath(), img);

            std::vector<std::unique_ptr<image_processor::AbstractFilter>> filters;
            parser.GetFilters(filters);

            image_processor::CompositeFilter composite(std::move(filters));
            composite.ApplyFilter(img);

            image_processor::BMPHandler::SaveFile(parser.GetOutputPath(), img);
        } else {
            cli::PrintInfo();
        }
    } catch (const std::exception& e) {
        std::cout << "Something went wrong:" << std::endl;
        std::cout << e.what() << std::endl << std::endl;
    }
    return 0;
}
