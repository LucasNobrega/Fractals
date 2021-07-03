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
    // Calculates # iterations for each pixel.
    if (_type == 1) {
        calculateIterationsMandelbrot();
    } else {
        calculateIterationsJulia();
    }

    // Calculates total iterations used for drawing the whole bitmap. Sums the iterations of all pixels.
    // It is used for the coloring.
    calculateTotalIterations();

    // Calculates how many pixels are in each color range.
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
            int iterations = Julia::getIterations(coords.first, coords.second, _startingC.first, _startingC.second);
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

    for (size_t y = 0; y < _height; y++) {
        for (size_t x = 0; x < _width; x++) {
            // For each pixel:

            int iterations = _fractal[y * _width + x];  // Number of iterations for given pixel

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

// Total of iterations for drawing the whole bitmap
void FractalCreator::calculateTotalIterations() {
    for (size_t i = 0; i < Mandelbrot::MAX_ITERATIONS; i++) {
        _total += _histogram[i];
    }
}

// Calculates how many pixels are in that color range.
void FractalCreator::calculateRangeTotals() {
    int rangeIndex = 0;

    for (int i = 0; i < Mandelbrot::MAX_ITERATIONS; i++) {
        int pixels = _histogram[i];     // How many pixels need that # of iterations.


        if (i >= _ranges[rangeIndex + 1]) {
            rangeIndex++;
        }

        _rangeTotals[rangeIndex] += pixels; 
    }
}

// Write in the Bitmap file.
void FractalCreator::writeBitmap(string name) { _bitmap.write(name); }

//
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

int FractalCreator::getType() { return _type; }

void FractalCreator::colorRangeFile(FractalCreator* fractalCreator1, string filename) {
    // Open file
    fstream colorFile;
    colorFile.open(filename, ios::in);

    // Check if it was properly opened
    if (!colorFile.is_open()) {
        cout << "Could not open color file." << endl;
    }

    string line = "";
    string stringRange = "";
    string stringRed = "";
    string stringGreen = "";
    string stringBlue = "";

    while (getline(colorFile, line)) {
        stringstream linestream(line);
        getline(linestream, stringRange, ' ');
        getline(linestream, stringRed, ' ');
        getline(linestream, stringGreen, ' ');
        getline(linestream, stringBlue, ' ');
        double range = stod(stringRange);
        double red = stoi(stringRed);
        double green = stoi(stringGreen);
        double blue = stoi(stringBlue);

        fractalCreator1->addRange(range, RGB(red, green, blue));
    }

    colorFile.close();
}

void FractalCreator::zoomAndPrint(FractalCreator* fractalCreator1, string filename) {
    // Open file
    fstream fractalFile;
    fractalFile.open(filename, ios::in);

    // Check if it was properly opened
    if (!fractalFile.is_open()) {
        cout << "Could not open fractal file." << endl;
    }

    string line = "";
    string operation = "";

    // Skips the 1st line (Mandelbrot-set) or the 1st and the 2nd line (Julia-set)
    if (fractalCreator1->getType() == 1) {
        getline(fractalFile, line);
    } else {
        getline(fractalFile, line);
        getline(fractalFile, line);
    }

    while (getline(fractalFile, line)) {
        stringstream linestream(line);
        getline(linestream, operation, ' ');

        if (operation == "z") {
            string stringX = "";
            string stringY = "";
            string stringScale = "";
            getline(linestream, stringX, ' ');
            getline(linestream, stringY, ' ');
            getline(linestream, stringScale, ' ');
            int x = stoi(stringX);
            int y = stoi(stringY);
            double scale = stod(stringScale);

            // cout << x << ", " << y << ", " << scale << endl;
            fractalCreator1->addZoom(Zoom(x, y, scale));
        } else if (operation == "p") {
            string printName = "";
            getline(linestream, printName);
            fractalCreator1->run(printName + ".bmp");
        }
    }

    // Close file
    fractalFile.close();
}

FractalCreator* fractalTypeInterpreter(string filename) {
    // Open file
    fstream fractalFile;
    fractalFile.open(filename, ios::in);

    // Check if it was properly opened
    if (!fractalFile.is_open()) {
        cout << "Could not open fractal file." << endl;
        return nullptr;
    }

    // Variables used to create the fractal
    int fractalType = 0;
    int dimX = 0;
    int dimY = 0;
    FractalCreator* pFractalCreator = nullptr;

    // Get fractal type and dimensions
    fractalFile >> fractalType >> dimX >> dimY;

    // Create specified fractal
    if (fractalType != 1 && fractalType != 2) {  // Invalid fractal type
        cout << "Fractal type not supported" << endl;
        return nullptr;

    } else if (fractalType == 1) {  // Create Mandelbrot-set fractal
        pFractalCreator = new FractalCreator(dimX, dimY, fractalType);

    } else if (fractalType == 2) {  // Create Julia-set fractal
        double cReal = 0.0;
        double cImag = 0.0;
        fractalFile >> cReal;
        fractalFile >> cImag;
        pFractalCreator = new FractalCreator(dimX, dimY, fractalType, pair<double, double>(cReal, cImag));
    }

    // Close file
    fractalFile.close();

    // Return pointer to created fractal
    return pFractalCreator;
}

}  // namespace fractal