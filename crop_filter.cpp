//
// Created by Алексей on 20.10.2026.
//

#include "crop_filter.h"

bool CropFilter::Apply(Bmp& picture) {
    Bmp::Bitmap& bitmap = picture.GetBitmap();
    bitmap.Crop(new_width_, new_height_);
    return true;
}