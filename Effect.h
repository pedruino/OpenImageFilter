#pragma once
#include "Bitmap.h"
#include "Color.h"
#include "kernels.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

class Effect
{
public:
	void Negative(Bitmap &image);
	void NegativeParallel(Bitmap & image, int thread_number);
	void Grayscale(Bitmap &image);
	void Blur(Bitmap &image);

	void Convolve(Bitmap & image);
	void Convolve(Bitmap & image, const double filterMatrix[][5], double factor, int bias, bool grayscale);

	Effect();
	~Effect();
};