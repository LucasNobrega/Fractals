#ifndef FRACTALCREATOR_H_
#define FRACTALCREATOR_H_
#include <math.h>

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "Bitmap.h"
#include "Mandelbrot.h"
#include "Julia.h"
#include "RGB.h"
#include "ZoomList.h"
using namespace std;

namespace fractal {
class FractalCreator {
   private:
    int _width;
    int _height;
    int _total{0};
    int _type{2};
    pair<double, double> _startingC = {-0.54, 0.54};
    unique_ptr<int[]> _histogram;  // Frequency of each # of iterations
                                   // needed. (Size:
                                   // Mandelbrot::MAX_ITERATIONS)
    unique_ptr<int[]> _fractal;    // Value of iterations for each pixel.
    Bitmap _bitmap;                // Bitmap created from # iterations for
                                   // each pixel
    ZoomList _zoomList;            // Zoom to be applied to picture.

    vector<int> _ranges;
    vector<RGB> _colors;
    vector<int> _rangeTotals;

    bool _bGotFirstRange{false};

   private:
    void calculateIterationsMandelbrot();  // How many iterations each
                                 // pixel need.
    void calculateIterationsJulia();
    void calculateTotalIterations();
    void calculateRangeTotals();
    void drawFractal();
    void writeBitmap(string name);
    int getRange(int iterations) const;

   public:
    FractalCreator(int width, int height, int type);
    FractalCreator(int width, int height, int type, pair<double, double> startingC);
    virtual ~FractalCreator();
    void addRange(double rangeEnd, const RGB& rgb);
    void addZoom(const Zoom& zoom);
    void run(string name);
};

}  // namespace fractal

#endif /* FRACTALCREATOR_H_ */