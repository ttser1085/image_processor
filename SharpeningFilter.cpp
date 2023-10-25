#include "SharpeningFilter.h"

static const image_processor::ConvFilter::Matrix MAT = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};

image_processor::SharpeningFilter::SharpeningFilter() : ConvFilter(MAT) {
}

image_processor::SharpeningFilter::~SharpeningFilter() = default;
