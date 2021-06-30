#include "FractalCreator.h"

#include <assert.h>

#include <iostream>

namespace fractal {

void FractalCreator::addZoom(const Zoom& zoom) { _zoomList.add(zoom); }

void FractalCreator::addRange(double rangeEnd, const RGB& rgb) {
    _ranges.push_back(rangeEnd * Mandelbrot::MAX_ITERATIONS);
    _colors.push_back(rgb);

    if (_bGotFirstRange) {
        _rangeTotals.push_back(0);
    }

    _bGotFirstRange = true;
}

void FractalCreator::run(string name) {
    // Calculate # iterations for each pixel.
    if (_type == 1) {
        calculateIterationsMandelbrot();
    } else {
        calculateIterationsJulia();
    }

    // Calculate total iterations used
    calculateTotalIterations();

    // Calculate color range
    calculateRangeTotals();

    // Draw colored pixel on Bitmap
    drawFractal();

    // Write Bitmap to file
    writeBitmap(name);
}

FractalCreator::FractalCreator(int width, int height, int type)
    : _width(width),
      _height(height),
      _histogram(new int[Mandelbrot::MAX_ITERATIONS]{0}),
      _fractal((new int[_width * _height]{0})),
      _bitmap(_width, _height),
      _zoomList(_width, _height),
      _type(type) {
    _zoomList.add(Zoom(_width / 2, _height / 2, 4.0 / _width));
}

FractalCreator::FractalCreator(int width, int height, int type, pair<double, double> startingC)
    : _width(width),
      _height(height),
      _histogram(new int[Mandelbrot::MAX_ITERATIONS]{0}),
      _fractal((new int[_width * _height]{0})),
      _bitmap(_width, _height),
      _zoomList(_width, _height),
      _type(type),
      _startingC(startingC) {
    _zoomList.add(Zoom(_width / 2, _height / 2, 4.0 / _width));
}

// Number of iterations for each pixel in the Zoomed-in screen.
void FractalCreator::calculateIterationsMandelbrot() {
    // For each pixel
    for (size_t y = 0; y < _height; y++) {
        for (size_t x = 0; x < _width; x++) {
            // Zoom in
            pair<double, double> coords = _zoomList.doZoom(x, y);

            // Get iteration for given pixel and store in buffer (_fractal)
            int iterations = Mandelbrot::getIterations(coords.first, coords.second);
            _fractal[y * _width + x] = iterations;

            // Update histogram.
            if (iterations != Mandelbrot::MAX_ITERATIONS) {
                _histogram[iterations]++;
            }
        }
    }
}

void FractalCreator::calculateIterationsJulia() {
    // For each pixel
    for (size_t y = 0; y < _height; y++) {
        for (size_t x = 0; x < _width; x++) {
            // Zoom in
            pair<double, double> coords = _zoomList.doZoom(x, y);

            // Get iteration for given pixel and store in buffer (_fractal)
            int iterations = Julia::getIterations(coords.first, coords.second, _startingC.first,
                                                  _startingC.second);
            _fractal[y * _width + x] = iterations;

            // Update histogram.
            if (iterations != Mandelbrot::MAX_ITERATIONS) {
                _histogram[iterations]++;
            }
        }
    }
}

// Create bitmap with values from the buffer.
void FractalCreator::drawFractal() {
    RGB startColor(0, 0, 0);
    RGB endColor(0, 0, 255);
    RGB colorDiff = endColor - startColor;

    // For each pixel:
    for (size_t y = 0; y < _height; y++) {
        for (size_t x = 0; x < _width; x++) {
            int iterations = _fractal[y * _width + x];

            int range = getRange(iterations);
            int rangeTotal = _rangeTotals[range];
            int rangeStart = _ranges[range];

            RGB& startColor = _colors[range];
            RGB& endColor = _colors[range + 1];
            RGB colorDiff = endColor - startColor;

            uint8_t red = 0;
            uint8_t green = 0;
            uint8_t blue = 0;

            // If the number of iterations if MAX_ITERATIONS, we leave it black.
            // Otherwise, we color it.
            if (iterations != Mandelbrot::MAX_ITERATIONS) {
                int totalPixels = 0;
                for (size_t i = rangeStart; i <= iterations; i++) {
                    totalPixels += (double)_histogram[i];
                }

                red = startColor.r + colorDiff.r * (double)totalPixels / rangeTotal;
                green = startColor.g + colorDiff.g * (double)totalPixels / rangeTotal;
                blue = startColor.b + colorDiff.b * (double)totalPixels / rangeTotal;
            }

            // Change the pixel in the bitmap.
            _bitmap.setPixel(x, y, red, green, blue);
        }
    }
}

void FractalCreator::calculateTotalIterations() {
    for (size_t i = 0; i < Mandelbrot::MAX_ITERATIONS; i++) {
        _total += _histogram[i];
    }
}

void FractalCreator::calculateRangeTotals() {
    int rangeIndex = 0;

    for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++) {
        int pixels = _histogram[i];

        if (i >= _ranges[rangeIndex + 1]) {
            rangeIndex++;
        }

        _rangeTotals[rangeIndex] += pixels;
    }
}

// Write in the Bitmap file.
void FractalCreator::writeBitmap(string name) { _bitmap.write(name); }

int FractalCreator::getRange(int iterations) const {
    int range = 0;

    for (size_t i = 1; i < _ranges.size(); i++) {
        range = i;
        if (_ranges[i] > iterations) {
            break;
        }
    }

    range--;
    assert(range > -1);
    assert(range < _ranges.size());

    return range;
}

FractalCreator::~FractalCreator(){};

}  // namespace fractal