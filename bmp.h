#ifndef IMAGE_PROCESSOR_BMP_H
#define IMAGE_PROCESSOR_BMP_H

#include "matrix.h"

#include <cstdint>
#include <fstream>
#include <vector>

using BYTE = char;
using WORD = uint16_t;
using DWORD = uint32_t;
using LONG = uint32_t;

extern const int BYTE_MAXVAL;
extern const int COLORS;

// 24 bytes
class __attribute__((packed)) Pixel {
public:
    explicit Pixel(uint8_t blue = 0, uint8_t green = 0, uint8_t red = 0) : blue_(blue), green_(green), red_(red) {
    }

    uint8_t& operator[](const int& ind);

    uint8_t GetVal() const;

private:
    uint8_t blue_;
    uint8_t green_;
    uint8_t red_;
};

extern const Pixel WHITE_PIX;
extern const Pixel BLACK_PIX;

// 14 bytes
class __attribute__((packed)) FileHeader {
public:
    WORD FileType;      /* File type, always 4D42h ("BM") */
    DWORD FileSize;     /* Size of the file in bytes */
    WORD Reserved1;     /* Always 0 */
    WORD Reserved2;     /* Always 0 */
    DWORD BitmapOffset; /* Starting position of image data in bytes */
};

// 40 bytes
class __attribute__((packed)) BitmapHeader {
public:
    DWORD Size;        /* Size of this header in bytes */
    LONG Width;        /* Image width in pixels */
    LONG Height;       /* Image height in pixels */
    WORD Planes;       /* Number of color planes */
    WORD BitsPerPixel; /* Number of bits per pixel */
    /* Fields added for Windows 3.x follow this line */
    DWORD Compression;     /* Compression methods used */
    DWORD SizeOfBitmap;    /* Size of bitmap in bytes */
    LONG HorzResolution;   /* Horizontal resolution in pixels per meter */
    LONG VertResolution;   /* Vertical resolution in pixels per meter */
    DWORD ColorsUsed;      /* Number of colors in the image */
    DWORD ColorsImportant; /* Minimum number of important colors */
};

class Bmp {
public:
    using Bitmap = Matrix<Pixel>;
    // using Bitmap = std::vector<std::vector<Pixel>>;

public:
    Bmp(){};

    size_t GetWidth() const {
        return bitmap_.GetColNum();
    }

    size_t GetHeight() const {
        return bitmap_.GetRowNum();
    }

    bool ReadBmp(const char* filename);

    bool WriteBmp(const char* filename);

    void UpdateBitmapHeader();

    void UpdateFileHeader();

    Bitmap& GetBitmap() {
        return bitmap_;
    }

    Pixel ApplyMatrix(size_t x, size_t y, const std::vector<std::vector<double>>& matrix);

private:
    void InitBitmap();

private:
    Bitmap bitmap_;
    FileHeader file_header_;
    BitmapHeader bitmap_header_;
};

int Normalize(int num, int min_val, int max_val);

double Normalize(double num, double min_val, double max_val);

template <typename T>
bool ReadBin(T& obj, std::istream& in);

template <>
bool ReadBin<Bmp::Bitmap>(Bmp::Bitmap& obj, std::istream& in);

template <typename T>
bool WriteBin(const T& obj, std::ostream& out);

template <>
bool WriteBin<Bmp::Bitmap>(const Bmp::Bitmap& obj, std::ostream& out);

#endif