#include "CrystallizeFilter.h"

#include <random>

static size_t SqrDist(const std::pair<size_t, size_t>& p1, const std::pair<size_t, size_t>& p2) {
    size_t dx = (p2.first >= p1.first ? p2.first - p1.first : p1.first - p2.first);
    size_t dy = (p2.second >= p1.second ? p2.second - p1.second : p1.second - p2.second);
    return dx * dx + dy * dy;
}

image_processor::CrystallizeFilter::CrystallizeFilter(size_t crystal_count) : crystal_count_(crystal_count) {
}

void image_processor::CrystallizeFilter::ApplyFilter(image_processor::Image& image) const {
    if (crystal_count_ > image.GetWidth() * image.GetHeight()) {
        throw std::invalid_argument("To big argument for Crystallize filter");
    }

    PointList crystals = GenCrystals(image.GetWidth(), image.GetHeight());

    size_t width = image.GetWidth();
    size_t height = image.GetHeight();

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            auto iter =
                std::min_element(crystals.begin(), crystals.end(),
                                 [x, y](const std::pair<size_t, size_t>& p1, const std::pair<size_t, size_t>& p2) {
                                     return SqrDist({x, y}, p1) < SqrDist({x, y}, p2);
                                 });

            image.SetPixel(x, y, image.GetPixel(iter->first, iter->second));
        }
    }
}

image_processor::CrystallizeFilter::PointList image_processor::CrystallizeFilter::GenCrystals(size_t width,
                                                                                              size_t height) const {
    static const int64_t SEED = 2282281085;
    std::mt19937 gen(SEED);
    std::uniform_int_distribution<size_t> distribution_x(0, width - 1);
    std::uniform_int_distribution<size_t> distribution_y(0, height - 1);

    PointList result;
    for (size_t i = 0; i < crystal_count_; ++i) {
        result.push_back({distribution_x(gen), distribution_y(gen)});
    }

    return result;
}

image_processor::CrystallizeFilter::~CrystallizeFilter() = default;
