#include "BMPHandler.h"

#include <cmath>
#include <limits>
#include <climits>

namespace {

#pragma pack(push, 1)
struct BMPHeader {
    uint16_t file_type;
    uint32_t file_size;
    uint32_t reserved;
    uint32_t data_offset;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct BMPInfo {
    uint32_t info_size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t image_size;
    int32_t resolution_x;
    int32_t resolution_y;
    uint32_t colors;
    uint32_t important_colors;
};
#pragma pack(pop)

struct Pixel {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
};

std::streamsize CalcPaddingSize(int32_t width) {
    const int32_t pxl_size = sizeof(Pixel);
    return (pxl_size + 1 - (width * pxl_size) % (pxl_size + 1)) %
           (pxl_size + 1);  // formula to calculate padding in bmp file with 24 bit pixels
}

uint32_t CalcFileSize(int32_t width, int32_t height, std::streamsize padding) {
    return sizeof(BMPHeader) + sizeof(BMPInfo) + width * height * sizeof(Pixel) + padding * height;
    // size of file = header + info + (pixel amount * pixel size) + (num of rows * padding size)
}

}  // namespace

namespace image_processor {

void BMPHandler::OpenFile(std::filesystem::path path, Image& img) {
    std::fstream stream;
    stream.open(path, std::ios_base::in | std::ios_base::binary);

    if (!stream.is_open()) {
        throw std::runtime_error("Could not open file " + path.string());
    }

    BMPHeader header;
    BMPInfo info;

    stream.read(reinterpret_cast<char*>(&header), sizeof(header));

    if (header.file_type != BMP_TYPE) {
        throw std::runtime_error("Input file is not BMP");
    }

    stream.read(reinterpret_cast<char*>(&info), sizeof(info));

    if (info.width <= 0) {
        throw std::runtime_error("Illegal width of input file");
    }

    if (info.planes != 1) {
        throw std::runtime_error("The number of color planes must be 1");
    }

    if (info.bits_per_pixel != sizeof(Pixel) * CHAR_BIT) {
        throw std::runtime_error("Pixel must be 24 bits");
    }

    if (info.compression) {
        throw std::runtime_error("Image must not be compressed");
    }

    if (info.colors || info.important_colors) {
        throw std::runtime_error("Color table detected");
    }

    std::streamsize padding_size = CalcPaddingSize(info.width);

    stream.seekg(header.data_offset, stream.beg);

    img = Image(info.width, info.height);
    for (int32_t y = 0; y < info.height; ++y) {
        for (int32_t x = 0; x < info.width; ++x) {
            Pixel pixel;
            stream.read(reinterpret_cast<char*>(&pixel), sizeof(pixel));
            size_t curr_y = info.height > 0 ? img.GetHeight() - 1 - y : y;
            img.SetPixel(x, curr_y,
                         {static_cast<double>(pixel.red) / static_cast<double>(std::numeric_limits<uint8_t>::max()),
                          static_cast<double>(pixel.green) / static_cast<double>(std::numeric_limits<uint8_t>::max()),
                          static_cast<double>(pixel.blue) / static_cast<double>(std::numeric_limits<uint8_t>::max())});
        }
        stream.ignore(padding_size);
    }
}

void BMPHandler::SaveFile(std::filesystem::path path, const Image& img) {
    std::fstream stream;
    stream.open(path, std::ios_base::out | std::ios_base::binary);

    if (!stream.is_open()) {
        throw std::runtime_error("Could not save in file " + path.string());
    }

    int32_t img_width = static_cast<int32_t>(img.GetWidth());
    int32_t img_height = static_cast<int32_t>(img.GetHeight());

    const uint8_t padding_buffer[3] = {0, 0, 0};
    std::streamsize padding_size = CalcPaddingSize(img_width);

    const uint32_t file_size = CalcFileSize(img_width, img_height, padding_size);

    const BMPHeader header = {BMP_TYPE, file_size, 0, sizeof(BMPHeader) + sizeof(BMPInfo)};

    const BMPInfo info = {sizeof(BMPInfo), img_width, img_height, 1, sizeof(Pixel) * CHAR_BIT, 0, 0, 0, 0, 0, 0};

    stream.write(reinterpret_cast<const char*>(&header), sizeof(header));
    stream.write(reinterpret_cast<const char*>(&info), sizeof(info));

    for (int32_t y = img_height - 1; y >= 0; --y) {
        for (int32_t x = 0; x < img_width; ++x) {
            auto color = img.GetPixel(x, y);

            Pixel pixel = {static_cast<uint8_t>(color.B * static_cast<double>(std::numeric_limits<uint8_t>::max())),
                           static_cast<uint8_t>(color.G * static_cast<double>(std::numeric_limits<uint8_t>::max())),
                           static_cast<uint8_t>(color.R * static_cast<double>(std::numeric_limits<uint8_t>::max()))};

            stream.write(reinterpret_cast<const char*>(&pixel), sizeof(pixel));
        }
        stream.write(reinterpret_cast<const char*>(&padding_buffer), padding_size);
    }
}
}  // namespace image_processor