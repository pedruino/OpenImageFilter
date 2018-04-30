#pragma once
#include <omp.h>
#include "Bitmap.h"
#include "Effect.h"
#include "math.h"
#include <string.h>
#include "functions.h"

////////////////////////////////////[ OPEN MP ]/////////////////////////////////////
#define OPEN_MP_TEST
#undef DEBUG
#include "Logger.h"
////////////////////////////////////////////////////////////////////////////////////

void main()
{
	double currentTime = 0;
	Logger* logger = new Logger();

	Bitmap* original = new Bitmap("./samples/original/hummingbird-squared.bmp");
	Bitmap* negative = original->Clone();
	Bitmap* grayscale = original->Clone();
	Bitmap* gaussian = original->Clone();
	Bitmap* laplace = original->Clone();
	Bitmap* sobel = original->Clone();
	Bitmap* prewitt = original->Clone();
	Bitmap* scharr = original->Clone();

	Effect effect;

#ifdef OPEN_MP_TEST
	for (size_t i = 0; i <= 1; i++)
	{
		Bitmap* negative = original->Clone();
		Bitmap* grayscale = original->Clone();

		int thread = pow(2, i);

		printf("Thread number [%d]: \n", thread);
		omp_set_num_threads(thread);

		currentTime = logger->CetCurrentTime();

		#pragma omp parallel
		{
			#pragma omp sections
			{
				#pragma omp section
				{
					effect.Grayscale(*grayscale);
#ifdef DEBUG
					logger->PrintCurrentThread();
#endif // DEBUG
				}

				#pragma omp section
				{
					effect.Negative(*negative);
#ifdef DEBUG
					logger->PrintCurrentThread();
#endif // DEBUG
				}
			}
		}

		logger->GetElapsedTime(currentTime);
	}

	negative->Save("./samples/negative.bmp");
	grayscale->Save("./samples/grayscale.bmp");

#endif // OPEN_MP_TEST

	////////////////////////////////////////// EXTRAS ///////////////////////////////
	// Uncomment below lines to get a pretty surprise
	omp_set_num_threads(1);
	// Gaussian filter - Apply 5x times (for fun)
	printf("Applying filter: Gaussian (5x)\n");
	currentTime = logger->CetCurrentTime();
	for (size_t i = 0; i < 5; i++)
		effect.Convolve(*gaussian, gaussian5x5, 1 / 230.f, 0, false);
	logger->GetElapsedTime(currentTime);

	// Laplacian filter
	printf("Applying filter: Laplacian\n");
	currentTime = logger->CetCurrentTime();
	effect.Convolve(*laplace, laplacian5x5, 1, 0, false);
	logger->GetElapsedTime(currentTime);

	// Sobel filter
	printf("Applying filter: Sobel\n");
	currentTime = logger->CetCurrentTime();
	effect.Convolve(*sobel, sobelx, sobely, 1, 0, true);
	logger->GetElapsedTime(currentTime);

	// Prewitt filter
	printf("Applying filter: Prewitt\n");
	currentTime = logger->CetCurrentTime();
	effect.Convolve(*prewitt, prewittx, prewitty, 1, 0, true);
	logger->GetElapsedTime(currentTime);

	// Scharr filter
	printf("Applying filter: Scharr\n");
	currentTime = logger->CetCurrentTime();
	effect.Convolve(*scharr, scharrx, scharry, 1, 0, true);
	logger->GetElapsedTime(currentTime);

	// Save to image files
	printf("Writing image files\n");
	original->Save("./samples/original.bmp");
	gaussian->Save("./samples/gaussian.bmp");
	laplace->Save("./samples/laplacian.bmp");
	sobel->Save("./samples/sobel.bmp");
	prewitt->Save("./samples/prewitt.bmp");
	scharr->Save("./samples/scharr.bmp");
	//////////////////////////////////////////////////////////////////////////////////////////////
}