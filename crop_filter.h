//
// Created by Алексей on 20.10.2026.
//

#ifndef IMAGE_PROCESSOR_CROP_FILTER_H
#define IMAGE_PROCESSOR_CROP_FILTER_H

#include "filter.h"

#include <set>

class CropFilter : public AbstractFilter {
public:
    CropFilter() : new_width_(), new_height_() {
    }

    explicit CropFilter(const FilterDescriptor& fd) : CropFilter() {
        if (names_.find(fd.name) == names_.end()) {
            throw std::invalid_argument("invalid filter name");
        }
        if (fd.args.size() != 2) {
            throw std::invalid_argument("invalid filter arguments");
        }
        new_width_ = atoi(fd.args[0]);
        new_height_ = atoi(fd.args[1]);
    }

    bool Apply(Bmp& picture) override;

private:
    int new_width_;
    int new_height_;
    const std::set<std::string> names_ = {"crop"};
};

#endif  // IMAGE_PROCESSOR_CROP_FILTER_H
