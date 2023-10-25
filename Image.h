#pragma once

#include <vector>

namespace image_processor {

class Image {
public:
    struct Color {
        bool operator==(const Color& other) const;

        double R;
        double G;
        double B;
    };

    using Channel = std::vector<std::vector<double>>;

    Image();

    Image(Image&& img) noexcept;

    Image(size_t width, size_t height);

    Image& operator=(Image&& img) noexcept;

    /*bool operator==(const Image& other) const;*/

    std::vector<Channel>& GetChannels();

    Color GetPixel(size_t x, size_t y) const;
    void SetPixel(size_t x, size_t y, Color color);

    size_t GetWidth() const;
    size_t GetHeight() const;

private:
    std::vector<Channel> channels_;
};

}  // namespace image_processor
