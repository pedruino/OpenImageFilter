#pragma once
#include "Bitmap.h"
#include <omp.h>
#include "functions.h"
#include "Logger.h"
#include "Color.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include "kernels.h"

class Effect
{
public:
	void Negative(Bitmap &image);
	void Grayscale(Bitmap &image);
	void Blur(Bitmap &image);

	void Convolve(Bitmap & image, const double xkernel[][3], const double ykernel[][3], double factor, int bias, bool grayscale);
	void Convolve(Bitmap & image, const double kernel[][5], double factor, int bias, bool grayscale);

	Effect();
	~Effect();
};