#pragma once

#include "ChannelWiseFilter.h"

namespace image_processor {

class ConvFilter : public ChannelWiseFilter {
public:
    using Matrix = std::vector<std::vector<double>>;

    explicit ConvFilter(const Matrix &matrix);

    ~ConvFilter() override;

protected:
    void FilterImpl(Image::Channel &channel) const final;

private:
    double MatrixResult(size_t xpos, size_t ypos, const Image::Channel &channel) const;

    Matrix matrix_;
};
}  // namespace image_processor