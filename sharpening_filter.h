//
// Created by Алексей on 22.10.2026.
//

#ifndef IMAGE_PROCESSOR_SHARPENING_FILTER_H
#define IMAGE_PROCESSOR_SHARPENING_FILTER_H

#include "filter.h"

#include <exception>
#include <set>

class SharpeningFilter : public AbstractFilter {
public:
    SharpeningFilter() {
    }

    explicit SharpeningFilter(const FilterDescriptor& fd) : SharpeningFilter() {
        if (names_.find(fd.name) == names_.end()) {
            throw std::invalid_argument("invalid filter name");
        }
        if (!fd.args.empty()) {
            throw std::invalid_argument("invalid filter arguments");
        }
    }

    bool Apply(Bmp& picture) override;

private:
    static const std::vector<std::vector<double>> MATRIX;
    const std::set<std::string> names_ = {"sharpening", "sharp"};
};
#endif  // IMAGE_PROCESSOR_SHARPENING_FILTER_H
