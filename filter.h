#ifndef IMAGE_PROCESSOR_FILTER_H
#define IMAGE_PROCESSOR_FILTER_H

#include "bmp.h"

class AbstractFilter {
public:
    // возвращает false если не удалось применить фильтр, true в противном случае
    virtual bool Apply(Bmp& picture) = 0;

    virtual ~AbstractFilter() {
    }
};

struct FilterDescriptor {
    const char* name;
    std::vector<const char*> args;
};

#endif