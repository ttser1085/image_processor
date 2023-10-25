#include "Image.h"

#include <stdexcept>

namespace image_processor {

bool Image::Color::operator==(const Image::Color& other) const {
    return R == other.R && G == other.G && B == other.B;
}

Image::Image() = default;

Image::Image(Image&& img) noexcept {
    if (this == &img) {
        return;
    }
    channels_ = std::move(img.channels_);
}

Image::Image(size_t width, size_t height) : channels_({Channel(height, std::vector<double>(width))}) {
}

Image& Image::operator=(Image&& img) noexcept {
    if (this != &img) {
        channels_ = std::move(img.channels_);
    }
    return *this;
}

/*bool Image::operator==(const Image& other) const {
    if (this == &other) {
        return true;
    }

    if (GetHeight() != other.GetHeight() || GetWidth() != other.GetWidth()) {
        return false;
    }

    if (channels_.size() == other.channels_.size()) {
        return channels_ == other.channels_;
    }

    if (channels_.empty() || other.channels_.empty()) {
        return false;
    }

    for (size_t y = 0; y < GetHeight(); ++y) {
        for (size_t x = 0; x < GetWidth(); ++x) {
            if (GetPixel(x, y) != other.GetPixel(x, y)) {
                return false;
            }
        }
    }

    return true;
}*/

std::vector<Image::Channel>& Image::GetChannels() {
    return channels_;
}

Image::Color Image::GetPixel(size_t x, size_t y) const {
    if (channels_.size() == 1) {
        return {channels_[0][y][x], channels_[0][y][x], channels_[0][y][x]};
    } else if (channels_.size() == 3) {
        return {channels_[0][y][x], channels_[1][y][x], channels_[2][y][x]};
    }

    throw std::runtime_error("Illegal number of channels");
}

void Image::SetPixel(size_t x, size_t y, Color color) {
    if (channels_.size() <= 1) {
        if (color.R == color.G && color.G == color.B) {
            channels_[0][y][x] = color.R;
        } else {
            if (channels_.size() == 1) {
                channels_.push_back(channels_[0]);
                channels_.push_back(channels_[0]);
            } else if (channels_.empty()) {
                channels_ = std::vector<Channel>(3);
            }

            channels_[0][y][x] = color.R;
            channels_[1][y][x] = color.G;
            channels_[2][y][x] = color.B;
        }
    } else if (channels_.size() == 3) {
        channels_[0][y][x] = color.R;
        channels_[1][y][x] = color.G;
        channels_[2][y][x] = color.B;
    } else {
        throw std::runtime_error("Illegal number of channels");
    }
}

size_t Image::GetWidth() const {
    return channels_[0][0].size();
}

size_t Image::GetHeight() const {
    return channels_[0].size();
}
}  // namespace image_processor