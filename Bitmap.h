#ifndef BITMAP_H_
#define BITMAP_H_

#include <cstdint>
#include <memory>
#include <string>

#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"
using namespace std;

namespace fractal {

class Bitmap {
   private:
    int _width{0};
    int _height{0};
    unique_ptr<uint8_t[]> _pPixels{nullptr};

   public:
    // Creator and Destroyer
    Bitmap(int width, int height);
    virtual ~Bitmap();

    // Create the bitmap
    void setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
    bool write(string filename);
};

}  // namespace fractal

#endif /* BITMAP_H_ */