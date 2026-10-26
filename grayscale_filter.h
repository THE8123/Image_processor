//
// Created by Алексей on 21.10.2026.
//

#ifndef IMAGE_PROCESSOR_GRAYSCALE_FILTER_H
#define IMAGE_PROCESSOR_GRAYSCALE_FILTER_H

#include "filter.h"

#include <set>

class GrayscaleFilter : public AbstractFilter {
public:
    GrayscaleFilter() {
    }

    explicit GrayscaleFilter(const FilterDescriptor& fd) : GrayscaleFilter() {
        if (names_.find(fd.name) == names_.end()) {
            throw std::invalid_argument("invalid filter name");
        }
        if (!fd.args.empty()) {
            throw std::invalid_argument("invalid filter arguments");
        }
    }

    bool Apply(Bmp& picture) override;

private:
    const std::set<std::string> names_ = {"grayscale", "gs"};
};

#endif  // IMAGE_PROCESSOR_GRAYSCALE_FILTER_H
