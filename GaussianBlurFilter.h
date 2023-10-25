#pragma once

#include "CompositeFilter.h"
#include "ConvFilter.h"

namespace image_processor {

class GaussianBlurFilter final : public CompositeFilter {
public:
    explicit GaussianBlurFilter(double sigma);

    ~GaussianBlurFilter() override;
};
}  // namespace image_processor