#pragma once
#include <omp.h>
#include "Bitmap.h"
#include "Effect.h"
#include "math.h"
#include <string.h>
#include "functions.h"

////////////////////////////////////[ OPEN MP ]/////////////////////////////////////
#undef OPEN_MP_TEST
#undef DEBUG
#include "Logger.h"
////////////////////////////////////////////////////////////////////////////////////

void main()
{
	double currentTime = 0;
	Logger* logger = new Logger();

	Bitmap* original = new Bitmap("./samples/original/profileimage.bmp");
	Bitmap* negative = original->Clone();
	Bitmap* grayscale = original->Clone();
	Bitmap* gaussian = original->Clone();
	Bitmap* sobel = original->Clone();

	Effect effect;

#ifdef OPEN_MP_TEST
	for (size_t i = 0; i <= 5; i++)
	{
		// Uncomment to clone
		//Bitmap* negative = original->Clone();
		//Bitmap* grayscale = original->Clone();

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

		// After all save file to hardrive
		//std::string fname_neg = std::string("./samples/negative_") + NumberToString(thread) + std::string(".bmp");
		//negative->Save(fname_neg.c_str());

		//std::string fname_gray = std::string("./samples/grayscale_") + NumberToString(thread) + std::string(".bmp");
		//grayscale->Save(fname_gray.c_str());
	}
#endif // OPEN_MP_TEST

	////////////////////////////////////////// EXTRAS ///////////////////////////////
	// Uncomment below lines to get a pretty surprise
	omp_set_num_threads(1);
	currentTime = logger->CetCurrentTime();
	effect.Negative(*negative);
	logger->GetElapsedTime(currentTime);

	// Current filter (SOBEL)
	currentTime = logger->CetCurrentTime();
	effect.Convolve(*sobel, sobelx, sobely, 1, 0, false);
	logger->GetElapsedTime(currentTime);

	// Apply 5x times (for fun)
	currentTime = logger->CetCurrentTime();
	for (size_t i = 0; i < 5; i++)
		effect.Convolve(*gaussian, gaussian5x5, 1 / 256.f, 0, false);
	logger->GetElapsedTime(currentTime);

	original->Save("./samples/original.bmp");
	sobel->Save("./samples/filter.sobel.bmp");
	gaussian->Save("./samples/gaussiano.bmp");
	//////////////////////////////////////////////////////////////////////////////////////////////

	negative->Save("./samples/negative.bmp");
	grayscale->Save("./samples/grayscale.bmp");
}