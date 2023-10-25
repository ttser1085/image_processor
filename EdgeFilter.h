#pragma once

#include "CompositeFilter.h"

namespace image_processor {

class EdgeFilter final : public CompositeFilter {
public:
    explicit EdgeFilter(double threshold);

    ~EdgeFilter() override;
};
}  // namespace image_processor
