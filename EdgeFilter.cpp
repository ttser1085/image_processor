#include "EdgeFilter.h"

#include "GrayscaleFilter.h"
#include "ConvFilter.h"
#include "ThresholdFilter.h"

image_processor::EdgeFilter::EdgeFilter(double threshold) {
    std::unique_ptr<AbstractFilter> gs = std::make_unique<GrayscaleFilter>();
    std::unique_ptr<AbstractFilter> conv =
        std::make_unique<ConvFilter>(ConvFilter::Matrix({{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}));
    std::unique_ptr<AbstractFilter> th = std::make_unique<ThresholdFilter>(threshold);

    AddFilter(std::move(gs));
    AddFilter(std::move(conv));
    AddFilter(std::move(th));
}

image_processor::EdgeFilter::~EdgeFilter() = default;
