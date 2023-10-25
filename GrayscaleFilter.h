#pragma once

#include "AbstractFilter.h"

namespace image_processor {

class GrayscaleFilter final : public AbstractFilter {
public:
    void ApplyFilter(Image &image) const final;

    ~GrayscaleFilter() override;
};
}  // namespace image_processor