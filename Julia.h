#ifndef JULIA_H_
#define JULIA_H_

using namespace std;

namespace fractal {

class Julia {
   public:
    static const int MAX_ITERATIONS = 1000;  // Max of iterations to test that pixel.

   public:
    // Creator and destroyer
    Julia();
    virtual ~Julia();

    // Calculates # of iterations for a given pixel.
    static int getIterations(double x, double y, double cReal, double cImag);
};

}  // namespace fractal

#endif /* JULIA_H_ */