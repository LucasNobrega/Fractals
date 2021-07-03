#include "Julia.h"

#include <complex>

using namespace std;
using namespace fractal;

namespace fractal {
Julia::Julia() {}

Julia::~Julia() {}

// Each pixel returns a different number of iterations.
// The color of the pixel will depend on how many iterations
// are needed to surpass the condition ( abs(z) > 2).
int Julia::getIterations(double x, double y, double cReal, double cImag) {
    complex<double> z(x, y);
    complex<double> c(cReal, cImag);

    int iterations = 0;

    while (iterations < MAX_ITERATIONS) {
        double xtemp = z.real() * z.real() - z.imag() * z.imag();
        z = complex<double>(xtemp + c.real(), 2 * z.real() * z.imag() + c.imag());

        if (abs(z) > 2) {
            break;
        }

        iterations++;
    }

    return iterations;
}

}  // namespace fractal