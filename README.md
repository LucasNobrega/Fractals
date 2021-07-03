# Fractals
Graphical C++ 11 application to draw a Mandelbrot-set fractal. This application was based on [John Purcell's implementation](https://github.com/caveofprogramming).

## The Application
This is a simple command line application that generates Mandebrot-set or Julia-set fractal images. Both the Mandelbrot's and the Julia's images are generated as bitmaps. The application takes 2 text files as inputs. The first file that should be passed as argument is the one that specifies the fractal images, we call it fractal.txt. The second file is the one that specifies the color ranges used for coloring the images.

### Fractal.txt
This file follows a simple format for generating fractal images. The first line of the file should be used for specifying the fractal type (1 for a Mandelbrot-set and 2 for a Julia-set) and the dimensions used for the bitmap. If the type defined is 2 (Julia-ser fractal), the second line of the file should specify the parameter C of the fractal.

The following lines represent operations to be applied to the fractal. Two types of operations are possible, Zoom and Print. Each line represents a operation. If the line starts with lower case "z", it represents a Zoom operation. Zoom operations should be followed by 3 arguments, the coordenates of where the zoom should be applied and the scale to be used. If the line starts with a lower case "p", it represents a Print operation. Such operation is used to output the bitmap created for such fractal. It requires the name of the file to be passed as argument.

Below we see two examples of Fractal text files. The first one generates a Manbrot-set fractal and the second one generates a Julia-set fractal.

```
** Mandelbrot.txt **  // Don't insert this line, nor the comments below
1 800 600             // Mandelbrot-set fractal. Bit map with dimensions 800 x 600.
p Mandelbrot_1        // Print bitmap with name "Mandebrot_1.bmp"
z 301 173 0.1         // Zoom in on pixel 301 x 173 with 0.1 scale.
p Mandelbrot_2        // Print bitmap with name "Mandelbrot_2.bmp"
z 562 381 0.1         // Zoom in on pixel 562 x 381 with 0.1 scale.
p Mandelbrot_3        // Print bitmap with name "Mandelbrot_3"
```

```
** Julia.txt **       // Don't insert this line, nor the comments below
2 1600 1200           // Julia-set fractal. Bit-map with dimensions 1600 x 1200.     
-0.54 0.54            // C = -0.54 + 0.54*i
p Julia_1             // Print bitmap with name "Julia_1.bmp"
z 992 816 0.1         // Zoom in on 992 x 816 with scale 0.1
p Julia_2             // Print bitmap with name "Julia_2.bmp"
z 514 574 0.1         // Zoom in on 514 x 574 with scale 0.1        
p Julia_3             // Print bitmap with name "Julia_3.bmp"
```

### Color.txt
This file format specifies the color ranges used for coloring the bitmap. Each line represents the limit of a color range. The first elements of the line should appear in crescenting order and should be a double-type between 0 and 1. The following numbers are the RGB components defined for that color range (varying from 0 to 255). Below we see an example file.

```
** color.txt **       // Don't insert this line, nor the comments below
0.0 0 7 100           // First color range is from 0.0 to 0.16
0.16 32 107 203
0.42 237 255 255
0.6425 255 170 0
0.8575 0 2 0
1.0 255 255 255       // The last color range is from 0.8575 to 1.0
```

## To do
- Optmize code
- Comment color-range algorithm
- Better structure the FractalCreator class, maybe by dividing in 2 other classes (FractalCreator and FilesHandler)
