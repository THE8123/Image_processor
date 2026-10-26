
// Created by Алексей on 22.10.2026.

#include "edge_filter.h"

const std::vector<std::vector<double>> EdgeFilter::MATRIX = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};

void EdgeFilter::SetGsFilter(AbstractFilter* gs_filter) {
    gs_filter_ = gs_filter;
}

bool EdgeFilter::Apply(Bmp& picture) {
    gs_filter_->Apply(picture);

    Bmp pic_copy = picture;
    size_t width = picture.GetWidth();
    size_t height = picture.GetHeight();
    Bmp::Bitmap& bitmap = picture.GetBitmap();
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            Pixel& pix = bitmap[i][j];
            pix = pic_copy.ApplyMatrix(i, j, MATRIX);
            if (static_cast<double>(pix.GetVal()) > treshold_ * BYTE_MAXVAL) {
                pix = BLACK_PIX;
            } else {
                pix = WHITE_PIX;
            }
        }
    }
    return true;
}