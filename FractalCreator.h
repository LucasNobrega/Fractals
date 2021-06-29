#ifndef FRACTALCREATOR_H_
#define FRACTALCREATOR_H_
#include <math.h>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include "Bitmap.h"
#include "Mandelbrot.h"
#include "ZoomList.h"
#include "RGB.h"
using namespace std;

namespace fractal {
class FractalCreator {
   private:
    int _width;
    int _height;
    int _total{0};
    unique_ptr<int[]> _histogram;
    unique_ptr<int[]> _fractal;
    Bitmap _bitmap;
    ZoomList _zoomList;

    vector<int> _ranges;
    vector<RGB> _colors;
    vector<int> _rangeTotals;

    bool _bGotFirstRange{false};

   private:
    void calculateIterations();
    void calculateTotalIterations();
    void calculateRangeTotals();
    void drawFractal();
    void writeBitmap(string name);
    int getRange(int iterations) const; 

   public:
    FractalCreator(int width, int height);
    virtual ~FractalCreator();
    void addRange(double rangeEnd, const RGB& rgb);
    void addZoom(const Zoom& zoom);
    void run(string name);
};

}  // namespace fractal

#endif /* FRACTALCREATOR_H_ */