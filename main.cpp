#include <iostream>
#include <sstream>

#include "FractalCreator.h"
#include "RGB.h"

using namespace std;
using namespace fractal;

int main(int argc, char** argv) {

    stringstream ss1;
    int fractalType; 

    if (argc != 1) {
        // Create Julia-set Fractal with dimensions 800 x 600
        stringstream ss2;
        stringstream ss3;
        double cReal, cImag;
        ss2 << argv[1];
        ss2 >> cReal;
        ss3 << argv[2];
        ss3 >> cImag;
        FractalCreator fractalCreator1(3200, 2400, 2, pair<double, double>(cReal, cImag));
        
        fractalCreator1.addRange(0.0, RGB(0, 0, 0));
        fractalCreator1.addRange(0.16, RGB(0, 0, 127));
        fractalCreator1.addRange(0.42, RGB(0, 127, 255));
        fractalCreator1.addRange(0.6425, RGB(255, 0, 127));
        fractalCreator1.addRange(0.8575, RGB(127, 0, 255));
        fractalCreator1.addRange(1.0, RGB(255, 255, 255));
        
        fractalCreator1.run("Julia_1.bmp");

        fractalCreator1.addZoom(Zoom(1536, 1816, 0.1));
        fractalCreator1.run("Julia_2.bmp");
        
        fractalCreator1.addZoom(Zoom(2800, 1168, 0.1));
        fractalCreator1.run("Julia_3.bmp");
        
        fractalCreator1.addZoom(Zoom(208, 2080, 0.05));
        fractalCreator1.run("Julia_4.bmp");

        fractalCreator1.addZoom(Zoom(1671, 1710, 0.05));
        fractalCreator1.run("Julia_5.bmp");

        fractalCreator1.addZoom(Zoom(1490, 1220, 0.05));
        fractalCreator1.run("Julia_6.bmp");
    } else {
        FractalCreator fractalCreator1(3200, 2400, 1);
        
        fractalCreator1.addRange(0.0, RGB(0, 7, 100));
        fractalCreator1.addRange(0.16, RGB(32, 107, 203));
        fractalCreator1.addRange(0.42, RGB(237, 255, 255));
        fractalCreator1.addRange(0.6425, RGB(255, 170, 0));
        fractalCreator1.addRange(0.8575, RGB(0, 2, 0));
        fractalCreator1.addRange(1.0, RGB(255, 255, 255));

        fractalCreator1.run("Mandelbrot_1.bmp");

        fractalCreator1.addZoom(Zoom(1180, 808, 0.1));
        fractalCreator1.run("Mandelbrot_2.bmp");

        fractalCreator1.addZoom(Zoom(1248, 1216, 0.1));
        fractalCreator1.run("Mandelbrot_3.bmp");

        fractalCreator1.addZoom(Zoom(2308, 1648, 0.1));
        fractalCreator1.run("Mandelbrot_4.bmp");

        fractalCreator1.addZoom(Zoom(1644, 1488, 0.1));
        fractalCreator1.run("Mandelbrot_5.bmp");

        fractalCreator1.addZoom(Zoom(2272, 548, 0.1));
        fractalCreator1.run("Mandelbrot_6.bmp");
    }

    cout << "Finished" << endl;
    return 0;
}