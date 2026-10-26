//
// Created by Алексей on 23.10.2026.
//

#include "blur_filter.h"
#include <cmath>

const double PI = acos(-1);
const int ENOUGH_SIZE = 6;
const size_t MAX_SIZE = 2048;

void BlurFilter::CreateMatrix() {
    size_t size = static_cast<uint8_t>(ceil(sigma_ * ENOUGH_SIZE)) + 1;
    size = std::min(MAX_SIZE, size);
    if (size % 2 == 0) {
        ++size;
    }
    matrix_h_.resize(1, std::vector<double>(size));
    matrix_v_.resize(size, std::vector<double>(1));

    int mid = static_cast<int>(size) / 2;
    double summary = 0;
    for (int i = 0; i < size; ++i) {
        double power = pow(mid - i, 2) / (2 * pow(sigma_, 2));
        double exponent = exp(-power);
        matrix_h_[0][i] = exponent / (sqrt(2 * PI) * sigma_);
        matrix_v_[i][0] = matrix_h_[0][i];
        summary += matrix_h_[0][i];
    }
    double mult = 1.0 / summary;
    for (int i = 0; i < size; ++i) {
        matrix_h_[0][i] *= mult;
        matrix_v_[i][0] *= mult;
    }
}

bool BlurFilter::Apply(Bmp& picture) {
    Bmp pic_copy = picture;
    size_t width = picture.GetWidth();
    size_t height = picture.GetHeight();
    // горизонтальный проход
    Bmp::Bitmap& bitmap = picture.GetBitmap();
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            Pixel& pix = bitmap[i][j];
            pix = pic_copy.ApplyMatrix(i, j, matrix_h_);
        }
    }
    // вертикальный проход
    Bmp pic_h = picture;
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            Pixel& pix = bitmap[i][j];
            pix = pic_h.ApplyMatrix(i, j, matrix_v_);
        }
    }
    return true;
}
