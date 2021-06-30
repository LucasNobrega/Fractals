# Fractals
Graphical C++ 11 application to draw a Mandelbrot-set fractal. This application was based on [John Purcell's implementation](https://github.com/caveofprogramming).

## The Application
This is a simple command line application that generates Mandebrot-set or Julia-set fractal images. Both the Mandelbrot's and the Julia's images are generated as bitmaps. Six images are generated for each type of fractal. Each image is a zommed-in version of the previous one. The coordinates and scales used for the zoom are hardcoded in the main.cpp file.

## Command line arguments
The type of fractal generated (Mandelbrot or Julia) can be chosen when excuting the application in the terminal.
- **Mandelbrot :** To generate Mandelbrot's Fractals simply compile the files with `make all` and execute the main without passing any arguments. This will generate 6 fractal images.

- **Julia :** To generate Julia-set's fractals, simply compile the files with `make all` and execute the main with the arguments needed. The first argument is the real part of the C parameter and the second argument is the imaginary part of such parameter. The images that will be generated correspond to Zoom-ins for when C = -0.4-0.59*i*.

## To do
- Let the user choose the zooms that should be applied to generate the next image. This could be made using command line arguments (x and y coordinates, scale, and file name) or reading a .txt file provided by the user.
- Let the user choose the color range used.
- Generate different types of fractals.
