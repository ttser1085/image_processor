#include "ThresholdFilter.h"

image_processor::ThresholdFilter::ThresholdFilter(double threshold) : threshold_(threshold) {
    if (threshold > 1 || threshold < 0) {
        throw std::invalid_argument("Threshold must ∈ [0; 1]");
    }
}

void image_processor::ThresholdFilter::FilterImpl(Image::Channel &channel) const {
    for (size_t y = 0; y < channel.size(); ++y) {
        for (size_t x = 0; x < channel[0].size(); ++x) {
            channel[y][x] = channel[y][x] > threshold_ ? 1.0 : 0.0;
        }
    }
}

image_processor::ThresholdFilter::~ThresholdFilter() = default;
