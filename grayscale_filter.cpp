//
// Created by Алексей on 21.10.2026.
//

#include "grayscale_filter.h"

const double REDC = 0.299;
const double GREENC = 0.587;
const double BLUEC = 0.114;

bool GrayscaleFilter::Apply(Bmp& picture) {
    Bmp::Bitmap& bitmap = picture.GetBitmap();
    size_t width = bitmap.GetColNum();
    size_t height = bitmap.GetRowNum();
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            Pixel& pix = bitmap[i][j];
            // pix[0] / BYTE_MAXVAL * REDC * BYTE_MAXVAL = pix[0] * REDC
            uint8_t new_col = static_cast<uint8_t>(REDC * pix[0] + GREENC * pix[1] + BLUEC * pix[2]);
            pix[0] = pix[1] = pix[2] = new_col;
        }
    }
    return true;
}
