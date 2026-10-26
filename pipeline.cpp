#include "pipeline.h"

bool Pipeline::Apply(Bmp& picture) {
    for (AbstractFilter* fl : filters_) {
        if (!fl) {
            return false;
        }
        bool filter_status = fl->Apply(picture);
        if (!filter_status) {
            return false;
        }
    }
    return true;
}

AbstractFilter* Pipeline::AddFilter(AbstractFilter* fl) {
    filters_.push_back(fl);
    return fl;
}

Pipeline::~Pipeline() {
    for (AbstractFilter* fl : filters_) {
        delete fl;
    }
}
