#pragma once

#include "ChannelWiseFilter.h"

namespace image_processor {

class ThresholdFilter : public ChannelWiseFilter {
public:
    explicit ThresholdFilter(double threshold);

    ~ThresholdFilter() override;

protected:
    void FilterImpl(Image::Channel &channel) const override;

private:
    double threshold_;
};
}  // namespace image_processor