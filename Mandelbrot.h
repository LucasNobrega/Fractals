#ifndef MANDELBROT_H_
#define MANDELBROT_H_

using namespace std;

namespace fractal {

class Mandelbrot {
   public:
    static const int MAX_ITERATIONS = 1000;  // Max of iterations to test that pixel.

   public:
    // Creator and destroyer
    Mandelbrot();
    virtual ~Mandelbrot();

    // Calculate # of iterations for a given pixel.
    static int getIterations(double x, double y);
};

}  // namespace fractal

#endif /* MANDELBROT_H_ */