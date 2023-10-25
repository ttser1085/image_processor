#include "GrayscaleFilter.h"

namespace image_processor {

void GrayscaleFilter::ApplyFilter(Image &image) const {
    const static double R_COEF = 0.299;
    const static double G_COEF = 0.587;
    const static double B_COEF = 0.114;

    auto &channels = image.GetChannels();
    if (channels.size() == 3) {
        for (size_t y = 0; y < channels[0].size(); ++y) {
            for (size_t x = 0; x < channels[0][0].size(); ++x) {
                auto color = image.GetPixel(x, y);
                channels[0][y][x] = R_COEF * color.R + G_COEF * color.G + B_COEF * color.B;
            }
        }

        channels.pop_back();
        channels.pop_back();
    } else if (channels.size() != 1) {
        throw std::runtime_error("Illegal number of channels");
    }
}

GrayscaleFilter::~GrayscaleFilter() = default;
}  // namespace image_processor