#pragma once

#include "Image.h"

#include <memory>

namespace image_processor {

class AbstractFilter {
public:
    virtual void ApplyFilter(Image &image) const = 0;

    virtual ~AbstractFilter();
};
}  // namespace image_processor