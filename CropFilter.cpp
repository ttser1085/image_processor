#include "CropFilter.h"

namespace image_processor {

CropFilter::CropFilter(size_t width, size_t height) : width_(width), height_(height) {
}

void CropFilter::FilterImpl(Image::Channel &channel) const {
    channel.resize(std::min(height_, channel.size()));
    for (auto &row : channel) {
        row.resize(std::min(width_, channel[0].size()));
    }
}

CropFilter::~CropFilter() = default;
}  // namespace image_processor