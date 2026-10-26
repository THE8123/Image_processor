//
// Created by Алексей on 19.10.2026.
//

#include "bmp.h"
#include "saturation_filter.h"

bool SaturationFilter::Apply(Bmp& picture) {
    size_t width = picture.GetWidth();
    size_t height = picture.GetHeight();
    Bmp::Bitmap& bitmap = picture.GetBitmap();
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            Pixel& pix = bitmap[i][j];
            for (int c = 0; c < 3; c++) {
                pix[c] =
                    static_cast<uint8_t>(Normalize(static_cast<double>(pix[c]) * saturation_ / BYTE_MAXVAL, 0.0, 1.0));
            }
        }
    }
    return true;
}
