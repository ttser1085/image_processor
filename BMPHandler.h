#pragma once

#include "Image.h"

#include <filesystem>
#include <fstream>

namespace image_processor {

class BMPHandler {
public:
    static void OpenFile(std::filesystem::path path, Image& img);

    static void SaveFile(std::filesystem::path path, const Image& img);

private:
    static const uint16_t BMP_TYPE = 0x4D42;
};
}  // namespace image_processor