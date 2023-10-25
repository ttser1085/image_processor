#include "ChannelWiseFilter.h"

void image_processor::ChannelWiseFilter::ApplyFilter(Image &image) const {
    for (auto &channel : image.GetChannels()) {
        FilterImpl(channel);
    }
}

image_processor::ChannelWiseFilter::~ChannelWiseFilter() = default;