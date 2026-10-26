//
// Created by Алексей on 23.10.2026.
//

#ifndef IMAGE_PROCESSOR_BLUR_FILTER_H
#define IMAGE_PROCESSOR_BLUR_FILTER_H

#include "filter.h"

#include <exception>
#include <set>

const double EPS = 1e-8;

class BlurFilter : public AbstractFilter {
public:
    BlurFilter() : sigma_() {
    }

    explicit BlurFilter(const FilterDescriptor& fd) : BlurFilter() {
        if (names_.find(fd.name) == names_.end()) {
            throw std::invalid_argument("invalid filter name");
        }
        if (fd.args.size() != 1) {
            throw std::invalid_argument("invalid filter arguments");
        }
        sigma_ = atof(fd.args[0]);
        if (sigma_ < EPS) {
            throw std::invalid_argument("sigma must be not 0");
        }
        CreateMatrix();
    }

    void CreateMatrix();

    bool Apply(Bmp& picture) override;

private:
    std::vector<std::vector<double>> matrix_v_;
    std::vector<std::vector<double>> matrix_h_;
    double sigma_;
    const std::set<std::string> names_ = {"blur"};
};

#endif  // IMAGE_PROCESSOR_BLUR_FILTER_H
