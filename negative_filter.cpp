//
// Created by Алексей on 21.10.2026.
//

#include "negative_filter.h"

bool NegativeFilter::Apply(Bmp& picture) {
    size_t width = picture.GetWidth();
    size_t height = picture.GetHeight();
    Bmp::Bitmap& bitmap = picture.GetBitmap();
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            Pixel& pix = bitmap[i][j];
            for (int c = 0; c < 3; c++) {
                pix[c] = BYTE_MAXVAL - pix[c];
            }
        }
    }
    return true;
}
