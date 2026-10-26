//
// Created by Алексей on 19.10.2026.
//

#ifndef IMAGE_PROCESSOR_REDUCE_FILTER_H
#define IMAGE_PROCESSOR_REDUCE_FILTER_H

#include "filter.h"

#include <set>

class SaturationFilter : public AbstractFilter {
public:
    SaturationFilter() : saturation_() {
    }

    explicit SaturationFilter(const FilterDescriptor& fd) : SaturationFilter() {
        if (names_.find(fd.name) == names_.end()) {
            throw std::invalid_argument("invalid filter name");
        }
        if (fd.args.size() != 1) {
            throw std::invalid_argument("invalid filter arguments");
        }
        saturation_ = atof(fd.args[0]);
    }

    bool Apply(Bmp& picture) override;

private:
    double saturation_;
    const std::set<std::string> names_ = {"saturation", "sat"};
};

#endif  // IMAGE_PROCESSOR_REDUCE_FILTER_H
