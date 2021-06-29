#ifndef MANDELBROT_H_
#define MANDELBROT_H_

using namespace std;

namespace fractal {

class Mandelbrot {
   public:
    static const int MAX_ITERATIONS = 1000;

   public:
    Mandelbrot();
    virtual ~Mandelbrot();

    static int getIterations(double x, double y);
};

}  // namespace fractal

#endif /* MANDELBROT_H_ */