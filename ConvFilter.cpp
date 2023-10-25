#include "ConvFilter.h"

namespace image_processor {

ConvFilter::ConvFilter(const Matrix &matrix) : matrix_(matrix) {
}

double ConvFilter::MatrixResult(size_t xpos, size_t ypos, const Image::Channel &channel) const {
    const ssize_t padding_x = static_cast<ssize_t>(matrix_[0].size()) / 2;
    const ssize_t padding_y = static_cast<ssize_t>(matrix_.size()) / 2;
    const ssize_t width = static_cast<ssize_t>(channel[0].size());
    const ssize_t height = static_cast<ssize_t>(channel.size());
    const ssize_t lx = static_cast<ssize_t>(xpos) - padding_x;
    const ssize_t ly = static_cast<ssize_t>(ypos) - padding_y;
    const ssize_t rx = static_cast<ssize_t>(xpos) + padding_x;
    const ssize_t ry = static_cast<ssize_t>(ypos) + padding_y;

    double result = 0;
    for (ssize_t y = ly; y <= ry; ++y) {
        for (ssize_t x = lx; x <= rx; ++x) {
            result += channel[std::min(height - 1, std::max(0l, y))][std::min(width - 1, std::max(0l, x))] *
                      matrix_[y - ly][x - lx];
        }
    }

    return std::min(1.0, std::max(0.0, result));
}

void ConvFilter::FilterImpl(Image::Channel &channel) const {
    Image::Channel new_channel(channel.size(), std::vector<double>(channel[0].size()));
    for (size_t y = 0; y < channel.size(); ++y) {
        for (size_t x = 0; x < channel[y].size(); ++x) {
            new_channel[y][x] = MatrixResult(x, y, channel);
        }
    }
    channel = std::move(new_channel);
}

ConvFilter::~ConvFilter() = default;
}  // namespace image_processor