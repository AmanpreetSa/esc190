#include "c_img.h"

double min(double a, double b)
{
    if (a <= b){
        return a;
    }
    else{
        return b;
    }
}

int main()
{
    struct rgb_img *im;
    read_in_img(&im, "image.bin");  // load in the image
    
    for (int i = 0; i < im->height; i++){
        for (int j = 0; j < im->width; j++){
            // get the r, g, b values at pixel (i, j)
            // multiply the value by 1.5
            // set the pixel (i, j) to the new value
            double r = min(get_pixel(im, i, j, 0) * 1.5, 255);
            double g = min(get_pixel(im, i, j, 1) * 1.5, 255);
            double b = min(get_pixel(im, i, j, 2) * 1.5, 255);
            set_pixel(im, i, j, (int)r, (int)g, (int)b);

            // get min b/c get_pixel could go above 255 (cap is 255 for uint_8 rgb) 
        }
    }

    write_img(im, "image_brighter.bin");
    return 0;
}

