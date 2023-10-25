#pragma once

#include "ChannelWiseFilter.h"

namespace image_processor {

class NegativeFilter final : public ChannelWiseFilter {
public:
    ~NegativeFilter() override;

protected:
    void FilterImpl(Image::Channel &channel) const final;
};
}  // namespace image_processor