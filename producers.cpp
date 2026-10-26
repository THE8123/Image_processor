#include "producers.h"

#include "blur_filter.h"
#include "crop_filter.h"
#include "edge_filter.h"
#include "grayscale_filter.h"
#include "negative_filter.h"
#include "saturation_filter.h"
#include "sharpening_filter.h"

AbstractFilter* MakeSaturationFilter(const FilterDescriptor& fd) {
    AbstractFilter* fl = new SaturationFilter(fd);
    return fl;
}

AbstractFilter* MakeCropFilter(const FilterDescriptor& fd) {
    AbstractFilter* fl = new CropFilter(fd);
    return fl;
}

AbstractFilter* MakeGrayscaleFilter(const FilterDescriptor& fd) {
    AbstractFilter* fl = new GrayscaleFilter(fd);
    return fl;
}

AbstractFilter* MakeNegativeFilter(const FilterDescriptor& fd) {
    AbstractFilter* fl = new NegativeFilter(fd);
    return fl;
}

AbstractFilter* MakeSharpeningFilter(const FilterDescriptor& fd) {
    AbstractFilter* fl = new SharpeningFilter(fd);
    return fl;
}

AbstractFilter* MakeEdgeFilter(const FilterDescriptor& fd) {
    EdgeFilter* fl = new EdgeFilter(fd);
    fl->SetGsFilter(MakeGrayscaleFilter({}));
    return static_cast<AbstractFilter*>(fl);
}

AbstractFilter* MakeBlurFilter(const FilterDescriptor& fd) {
    AbstractFilter* fl = new BlurFilter(fd);
    return fl;
}
