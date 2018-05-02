//
// Created by pedruino on 5/1/18.
//

#ifndef OPENIMAGEFILTER_FILTER_H
#define OPENIMAGEFILTER_FILTER_H


#include "Bitmap.h"

class Filter {

public:
    Filter();
    ~Filter();

    void Convolve(Bitmap & image, const double kernel[][5], double factor, int bias, bool grayscale);

    void Convolve(Bitmap & image, const double xkernel[][3], const double ykernel[][3], double factor, int bias, bool grayscale);

    void Grayscale(Bitmap &image);

    void Negative(Bitmap &image);

    void Blur(Bitmap &image);
};


#endif //OPENIMAGEFILTER_FILTER_H
