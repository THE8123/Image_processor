#ifndef IMAGE_PROCESSOR_PIPELINE_H
#define IMAGE_PROCESSOR_PIPELINE_H

#include <vector>

#include "bmp.h"
#include "filter.h"

class Pipeline {
public:
    AbstractFilter* AddFilter(AbstractFilter*);

    bool Apply(Bmp& picture);

    Pipeline() {
    }

    ~Pipeline();

    Pipeline& operator=(const Pipeline& rhs) = delete;

    Pipeline(const Pipeline& other) = delete;

private:
    std::vector<AbstractFilter*> filters_;
};

#endif