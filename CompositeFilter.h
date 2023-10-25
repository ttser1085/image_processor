#pragma once

#include "AbstractFilter.h"

#include <vector>

namespace image_processor {

class CompositeFilter : public AbstractFilter {
public:
    CompositeFilter();

    explicit CompositeFilter(std::vector<std::unique_ptr<AbstractFilter>> filters);

    void ApplyFilter(Image &image) const final;

    ~CompositeFilter() override;

protected:
    void AddFilter(std::unique_ptr<AbstractFilter> filter);

private:
    std::vector<std::unique_ptr<AbstractFilter>> filters_;
};
}  // namespace image_processor