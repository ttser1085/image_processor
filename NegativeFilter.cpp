#include "NegativeFilter.h"

void image_processor::NegativeFilter::FilterImpl(Image::Channel &channel) const {
    for (size_t y = 0; y < channel.size(); ++y) {
        for (size_t x = 0; x < channel[0].size(); ++x) {
            channel[y][x] = 1 - channel[y][x];
        }
    }
}

image_processor::NegativeFilter::~NegativeFilter() = default;
