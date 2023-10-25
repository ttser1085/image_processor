#pragma once

#include "AbstractFilter.h"

namespace image_processor {

class ChannelWiseFilter : public AbstractFilter {
public:
    void ApplyFilter(Image &image) const final;

    ~ChannelWiseFilter() override;

protected:
    virtual void FilterImpl(Image::Channel &channel) const = 0;
};
}  // namespace image_processor