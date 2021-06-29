#ifndef BITMAPFILEHEADER_H_
#define BITMAPFILEHEADER_H_

#include <cstdint>
using namespace std;

#pragma pack(push, 2)  // So it doesn't do any padding, nor memory optimization.

namespace fractal {

struct BitmapFileHeader {
    char header[2] = {'B', 'M'};
    int32_t fileSize;
    int32_t reserved{0};
    int32_t dataOffset;
};

#pragma pack(pop)

}  // namespace fractal

#endif /* BITMAPFILEHEADER_H_ */