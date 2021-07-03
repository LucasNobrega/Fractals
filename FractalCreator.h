#ifndef FRACTALCREATOR_H_
#define FRACTALCREATOR_H_
#include <math.h>

#include <cstdint>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "Bitmap.h"
#include "Julia.h"
#include "Mandelbrot.h"
#include "RGB.h"
#include "ZoomList.h"
using namespace std;

namespace fractal {
class FractalCreator {
   private:
    int _type{2};                                     // A fractal can be Mandelbrot-set, Julia-set, ...
    int _width;                                       // Width of generated image
    int _height;                                      // Height of generated image
    pair<double, double> _startingC = {-0.54, 0.54};  // For a Julia-set fractal, we need a starting point C

    unique_ptr<int[]> _histogram;  // Frequency of each # of iterations needed. (Size: Mandelbrot::MAX_ITERATIONS)
    unique_ptr<int[]> _fractal;    // Value of iterations for each pixel. (Size: _width * _height)
    Bitmap _bitmap;                // Bitmap created from # iterations for each pixel
    ZoomList _zoomList;            // Zooms to be applied to picture.

    int _total{0};              // How many iterations are needed for drawing the whole bitmap
    vector<int> _ranges;
    vector<RGB> _colors;
    vector<int> _rangeTotals;

    bool _bGotFirstRange{false};

   private:
    void calculateIterationsMandelbrot();  // Calculates how many iterations for each pixel on the bitmap
    void calculateIterationsJulia();       // Calculates how many iterations for each pixel on the bitmap
    void calculateTotalIterations();
    void calculateRangeTotals();
    void drawFractal();             // Draws bitmap with values from the _fractals and _histogram buffers
    void writeBitmap(string name);  // Writes the .bmp file
    int getRange(int iterations) const;

   public:
    // Constructors and destructor
    FractalCreator(int width, int height, int type, pair<double, double> startingC);  // Julia-set's fractal constructor
    FractalCreator(int width, int height, int type);  // Mandelbrot-set's fractal constructor
    virtual ~FractalCreator();                        // Destructor

    // Getters
    int getType();  // Get the type of fractal

    // Methods for creating creating the Fractals
    void run(string name);                           // Used to actually create the fractal using all methods
    void addZoom(const Zoom &zoom);                  // Adds zoom to Zoomlist
    void addRange(double rangeEnd, const RGB &rgb);  // Adds a Range to color range

    void colorRangeFile(FractalCreator *fractalCreator1,
                        string filename);  // Reads the color ranges files and adds specified ranges
    
    void zoomAndPrint(FractalCreator *fractalCreator1,
                      string filename);  // Reads the Fractal specifier file and applies the specified zooms, and runs
                                         // and prints the specified.bmp files
};

FractalCreator *fractalTypeInterpreter(
    string filename);  // Reads the Fractal specifier file and calls respective constructor
}  // namespace fractal

#endif /* FRACTALCREATOR_H_ */