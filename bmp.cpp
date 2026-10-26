//
// Created by Алексей on 18.10.2026.
//
#include "bmp.h"

#include <fstream>
#include <functional>
#include <ios>
#include <stdexcept>

const uint8_t NULL_BYTE = 0;
const int BYTE_MAXVAL = (1 << sizeof(BYTE) * 8) - 1;
const int COLORS = 3;

const Pixel WHITE_PIX = Pixel(0, 0, 0);
const Pixel BLACK_PIX = Pixel(BYTE_MAXVAL, BYTE_MAXVAL, BYTE_MAXVAL);

uint8_t& Pixel::operator[](const int& ind) {
    switch (ind) {
        case 0:
            return red_;
        case 1:
            return green_;
        case 2:
            return blue_;
        default:
            throw std::out_of_range("Индекс цвета пикселя от 0 до 2");
    }
}

uint8_t Pixel::GetVal() const {
    return (red_ / 3 + blue_ / 3 + green_ / 3);
}

void Bmp::InitBitmap() {
    size_t height = bitmap_header_.Height;
    size_t width = bitmap_header_.Width;
    bitmap_.Init(height, width);
}

bool Bmp::ReadBmp(const char* filename) {
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    if (!ReadBin(file_header_, file)) {
        return false;
    }
    if (!ReadBin(bitmap_header_, file)) {
        return false;
    }
    InitBitmap();
    if (!ReadBin(bitmap_, file)) {
        return false;
    }
    file.close();
    return true;
}

bool Bmp::WriteBmp(const char* filename) {
    std::ofstream file(filename, std::ios::out | std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    UpdateBitmapHeader();
    UpdateFileHeader();

    if (!WriteBin(file_header_, file)) {
        return false;
    }
    if (!WriteBin(bitmap_header_, file)) {
        return false;
    }
    if (!WriteBin(bitmap_, file)) {
        return false;
    }
    file.close();
    return true;
}

template <typename T>
bool ReadBin(T& obj, std::istream& in) {
    in.read(reinterpret_cast<char*>(&obj), sizeof(obj));
    if (!in) {
        return false;
    }
    return true;
}

template <typename T>
bool WriteBin(const T& obj, std::ostream& out) {
    out.write(reinterpret_cast<const char*>(&obj), sizeof(obj));
    if (!out) {
        return false;
    }
    return true;
}

template <>
bool ReadBin<Bmp::Bitmap>(Bmp::Bitmap& obj, std::istream& in) {
    size_t height = obj.GetRowNum();
    size_t width = obj.GetColNum();
    int64_t padding = static_cast<int64_t>((4 - width * 3 % 4) % 4);
    for (size_t i = height; i-- > 0;) {
        for (size_t j = 0; j < width; j++) {
            in.read(reinterpret_cast<char*>(&obj[i][j]), sizeof(obj[i][j]));
            if (!in) {
                return false;
            }
        }
        in.seekg(padding, std::ios::cur);
        if (!in) {
            return false;
        }
    }
    return true;
}

template <>
bool WriteBin<>(const Bmp::Bitmap& obj, std::ostream& out) {
    size_t height = obj.GetRowNum();
    size_t width = obj.GetColNum();
    size_t padding = (4 - width * 3 % 4) % 4;
    for (size_t i = height; i-- > 0;) {
        for (size_t j = 0; j < width; j++) {
            out.write(reinterpret_cast<const char*>(&obj[i][j]), sizeof(obj[i][j]));
            if (!out) {
                return false;
            }
        }
        for (size_t pd = 0; pd < padding; pd++) {
            out.write(reinterpret_cast<const char*>(&NULL_BYTE), sizeof(NULL_BYTE));
            if (!out) {
                return false;
            }
        }
    }
    return true;
}

void Bmp::UpdateBitmapHeader() {
    bitmap_header_.Width = GetWidth();
    bitmap_header_.Height = GetHeight();
}

void Bmp::UpdateFileHeader() {
    file_header_.FileSize = sizeof(FileHeader) + sizeof(BitmapHeader) + sizeof(Pixel) * GetHeight() * GetWidth();
}

double Normalize(double num, double min_val, double max_val) {
    return std::max(min_val, std::min(max_val, num));
}

int Normalize(int num, int min_val, int max_val) {
    return std::max(min_val, std::min(max_val, num));
}

Pixel Bmp::ApplyMatrix(size_t x, size_t y, const std::vector<std::vector<double>>& matrix) {
    if (matrix.size() % 2 == 0 || matrix[0].size() % 2 == 0) {
        throw std::invalid_argument("Применяемая матрица должна быть нечетных размеров");
    }
    size_t width = matrix[0].size();
    int add_w = static_cast<int>(width) / 2;
    size_t height = matrix.size();
    int add_h = static_cast<int>(height) / 2;
    double red = 0;
    double green = 0;
    double blue = 0;
    std::function<double&(int)> col = [&](int i) -> double& {
        switch (i) {
            case 0:
                return red;
            case 1:
                return green;
            case 2:
                return blue;
            default:
                throw std::out_of_range("Индекс цвета пикселя от 0 до 2");
        }
    };

    int i_start = -add_h + static_cast<int>(x);
    int j_start = -add_w + static_cast<int>(y);
    for (int i = i_start; i <= i_start + add_h * 2; i++) {
        for (int j = j_start; j <= j_start + add_w * 2; j++) {
            int idx_i = Normalize(i, 0, static_cast<int>(GetHeight()) - 1);
            int idx_j = Normalize(j, 0, static_cast<int>(GetWidth()) - 1);
            Pixel& pix = bitmap_[idx_i][idx_j];
            for (int c = 0; c < COLORS; c++) {
                col(c) += matrix[i - i_start][j - j_start] * pix[c] / BYTE_MAXVAL;
            }
        }
    }
    red = Normalize(red, 0.0, 1.0) * BYTE_MAXVAL;
    green = Normalize(green, 0.0, 1.0) * BYTE_MAXVAL;
    blue = Normalize(blue, 0.0, 1.0) * BYTE_MAXVAL;
    Pixel res(static_cast<uint8_t>(red), static_cast<uint8_t>(green), static_cast<uint8_t>(blue));
    return res;
}
