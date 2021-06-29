#include <iostream>
#include "FractalCreator.h"
#include "RGB.h"

using namespace std;
using namespace fractal;

int main() {

    FractalCreator fractalCreator1(800, 600);
    
    fractalCreator1.addRange(0.0, RGB(0, 0, 0));
    fractalCreator1.addRange(0.3, RGB(255, 0, 0));
    fractalCreator1.addRange(0.5, RGB(255, 255, 0));
    fractalCreator1.addRange(1.0, RGB(255, 255, 255));
    
    fractalCreator1.addZoom(Zoom(295, 202, 0.1));
    fractalCreator1.addZoom(Zoom(312, 304, 0.1));
    

    fractalCreator1.run("test.bmp");


    cout << "Finished" << endl;
    return 0;
}