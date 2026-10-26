//
// Created by Алексей on 22.10.2026.
//

#ifndef IMAGE_PROCESSOR_EDGE_FILTER_H
#define IMAGE_PROCESSOR_EDGE_FILTER_H

#include "filter.h"

#include <set>

class EdgeFilter : public AbstractFilter {
public:
    EdgeFilter() : treshold_() {
    }

    explicit EdgeFilter(const FilterDescriptor& fd) : EdgeFilter() {
        if (names_.find(fd.name) == names_.end()) {
            throw std::invalid_argument("invalid filter name");
        }
        if (fd.args.size() != 1) {
            throw std::invalid_argument("invalid filter arguments");
        }
        treshold_ = atof(fd.args[0]);
    }

    void SetGsFilter(AbstractFilter* gs_filter);

    bool Apply(Bmp& picture) override;

private:
    double treshold_;
    AbstractFilter* gs_filter_ = nullptr;
    static const std::vector<std::vector<double>> MATRIX;
    const std::set<std::string> names_ = {"edge"};
};

#endif  // IMAGE_PROCESSOR_EDGE_FILTER_H
