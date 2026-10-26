//
// Created by Алексей on 22.10.2026.
//

#include "sharpening_filter.h"

const std::vector<std::vector<double>> SharpeningFilter::MATRIX = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};

bool SharpeningFilter::Apply(Bmp& picture) {
    Bmp pic_copy = picture;
    size_t width = picture.GetWidth();
    size_t height = picture.GetHeight();
    Bmp::Bitmap& bitmap = picture.GetBitmap();
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            Pixel& pix = bitmap[i][j];
            pix = pic_copy.ApplyMatrix(i, j, MATRIX);
        }
    }
    return true;
}
