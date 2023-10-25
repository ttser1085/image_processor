#pragma once

#include "ConvFilter.h"

namespace image_processor {

class SharpeningFilter final : public ConvFilter {
public:
    SharpeningFilter();

    ~SharpeningFilter() override;
};
}  // namespace image_processor