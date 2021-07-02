#include <iostream>

#include "FractalCreator.h"
#include "RGB.h"

using namespace std;
using namespace fractal;


int main(int argc, char **argv) {
    stringstream ss1;
    int fractalType;

    FractalCreator *fractalCreator1 = fractalTypeInterpreter(argv[1]);
    if (fractalCreator1 == nullptr) {
        cout << "Error creating fractal." << endl;
        return -1;
    }
    fractalCreator1->colorRangeFile(fractalCreator1, argv[2]);
    fractalCreator1->zoomAndPrint(fractalCreator1, argv[1]);
    
    cout << "Finished" << endl;
    return 0;
}

