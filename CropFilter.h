#pragma once

#include "ChannelWiseFilter.h"

namespace image_processor {
class CropFilter final : public ChannelWiseFilter {
public:
    CropFilter(size_t width, size_t height);

    ~CropFilter() override;

protected:
    void FilterImpl(Image::Channel &channel) const final;

private:
    size_t width_;
    size_t height_;
};
}  // namespace image_processor