#ifndef RGB_H_
#define RGB_H_

namespace fractal {

// Each pixel will be represented by 3 values. One for each
// component of the RGB spectrum.
struct RGB {
    double r;
    double g;
    double b;

    RGB(double r, double g, double b);
};

RGB operator-(const RGB& first, const RGB& second);

}  // namespace fractal

#endif /* RGB_H_ */