#pragma once

#include "AbstractFilter.h"

namespace image_processor {

class CrystallizeFilter final : public AbstractFilter {
public:
    explicit CrystallizeFilter(size_t crystal_count);

    ~CrystallizeFilter() override;

    void ApplyFilter(Image &image) const final;

private:
    using PointList = std::vector<std::pair<size_t, size_t>>;

    PointList GenCrystals(size_t width, size_t height) const;

    size_t crystal_count_;
};
}  // namespace image_processor