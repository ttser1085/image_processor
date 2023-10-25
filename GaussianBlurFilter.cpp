#include "GaussianBlurFilter.h"

#include <cmath>

namespace {

double Gauss(double sigma, ssize_t x, ssize_t y) {
    return std::exp(-static_cast<double>(x * x + y * y) / (2 * sigma * sigma)) / (2 * std::numbers::pi * sigma * sigma);
}

image_processor::ConvFilter::Matrix GenGaussMatrix(double sigma, size_t width, size_t height) {
    const ssize_t radius_x = static_cast<ssize_t>(width) / 2;
    const ssize_t radius_y = static_cast<ssize_t>(height) / 2;

    image_processor::ConvFilter::Matrix result(height, std::vector<double>(width));
    double sum = 0;
    for (ssize_t y = -radius_y; y <= radius_y; ++y) {
        for (ssize_t x = -radius_x; x <= radius_x; ++x) {
            result[y + radius_y][x + radius_x] = Gauss(sigma, x, y);
            sum += result[y + radius_y][x + radius_x];
        }
    }

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            result[y][x] /= sum;
        }
    }

    return result;
}
}  // namespace

image_processor::GaussianBlurFilter::GaussianBlurFilter(double sigma) {
    if (sigma == 0) {
        throw std::invalid_argument("Sigma must be != 0");
    }

    // size of matrix - odd(3 * sigma)
    const size_t size = static_cast<size_t>(std::ceil(3 * sigma)) + static_cast<size_t>(std::ceil(3 * sigma)) % 2 + 3;

    AddFilter(std::make_unique<ConvFilter>(GenGaussMatrix(sigma, size, 1)));
    AddFilter(std::make_unique<ConvFilter>(GenGaussMatrix(sigma, 1, size)));
}

image_processor::GaussianBlurFilter::~GaussianBlurFilter() = default;
