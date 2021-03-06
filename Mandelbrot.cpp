#include "Mandelbrot.h"

#include <complex>

using namespace std;
using namespace fractal;

namespace fractal {
Mandelbrot::Mandelbrot() {}

Mandelbrot::~Mandelbrot() {}

// Each pixel returns a different number of iterations.
// The color of the pixel will depend on how many iterations
// are needed to surpass the condition ( abs(z) > 2).
int Mandelbrot::getIterations(double x, double y) {
    complex<double> z = 0;
    complex<double> c(x, y);

    int iterations = 0;

    while (iterations < MAX_ITERATIONS) {
        z = z * z + c;

        if (abs(z) > 2) {
            break;
        }

        iterations++;
    }

    return iterations;
}

}  // namespace fractal