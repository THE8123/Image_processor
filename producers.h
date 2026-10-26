#ifndef IMAGE_PROCESSOR_PRODUCERS_H
#define IMAGE_PROCESSOR_PRODUCERS_H

#include "filter.h"
#include "parser.h"

AbstractFilter* MakeSaturationFilter(const FilterDescriptor& fd);

AbstractFilter* MakeCropFilter(const FilterDescriptor& fd);

AbstractFilter* MakeGrayscaleFilter(const FilterDescriptor& fd);

AbstractFilter* MakeNegativeFilter(const FilterDescriptor& fd);

AbstractFilter* MakeSharpeningFilter(const FilterDescriptor& fd);

AbstractFilter* MakeEdgeFilter(const FilterDescriptor& fd);

AbstractFilter* MakeBlurFilter(const FilterDescriptor& fd);

// ...

#endif