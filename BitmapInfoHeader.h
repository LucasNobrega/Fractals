#ifndef BITMAPINFOHEADER_H_
#define BITMAPINFOHEADER_H_

#include <cstdint>
using namespace std;

#pragma pack(push, 2)

namespace fractal {

// Device-Independent Bitmap Hedaer (fixed size: 40 bytes)
struct BitmapInfoHeader {
    int32_t headerSize{40};
    int32_t width;   // Width of the bitmap
    int32_t height;  // Height of the bitmap
    int16_t planes{1};
    int16_t bitsPerPixel{24};  // One byte for each color (RGB)
    int32_t compression{0};
    int32_t dataSize{0};
    int32_t horizontalResolution{2400};
    int32_t verticalResolution{2400};
    int32_t colors{0};
    int32_t importantColors{0};
};

#pragma pack(pop)

}  // namespace fractal

#endif /* BITMAPINFOHEADER_H_ */