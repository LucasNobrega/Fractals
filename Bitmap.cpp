#include "Bitmap.h"

#include <fstream>
#include <iostream>

#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"

using namespace std;
using namespace fractal;

namespace fractal {

Bitmap::Bitmap(int width, int height)
    : _width(width), _height(height), _pPixels(new uint8_t[3 * width * height]) {}

Bitmap::~Bitmap() {}

bool Bitmap::write(string filename) {
    BitmapFileHeader fileHeader;
    BitmapInfoHeader infoHeader;

    // File Header
    fileHeader.fileSize =
        sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader) + (3 * _width * _height);
    fileHeader.dataOffset = sizeof(BitmapFileHeader) + sizeof(BitmapInfoHeader);

    // Info Header
    infoHeader.width = _width;
    infoHeader.height = _height;

    // Opening file
    ofstream outputFile;
    outputFile.open(filename, ios::binary);
    if (!outputFile) {
        return false;
    }

    // Write Headers and pixels
    outputFile.write(reinterpret_cast<char *>(&fileHeader), sizeof(fileHeader));
    outputFile.write(reinterpret_cast<char *>(&infoHeader), sizeof(infoHeader));
    outputFile.write(reinterpret_cast<char *>(_pPixels.get()), 3 * _height * _width);

    // Closing file
    outputFile.close();
    if (!outputFile) {
        return false;
    }

    return true;
}

// Give each pixel a RGB value for each component.
void Bitmap::setPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue) {
    uint8_t *pPixel = _pPixels.get();  // Can't assign because _pPixels is an unique_ptr

    pPixel += (3 * y * _width) + (3 * x);

    pPixel[0] = blue;  // Bitmap is little-endian
    pPixel[1] = green;
    pPixel[2] = red;
}

}  // namespace fractal