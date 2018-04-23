#include <omp.h>
#include "Bitmap.h"
#include "Effect.h"
#include "math.h"
#include <string.h>
#include "functions.h"

#define KERNELS_H
////////////////////////////////////[ OPEN MP ]/////////////////////////////////////
#undef DEBUG
#include "Logger.h"
#include "main.h"
#define THREAD_NUMBERS 4
////////////////////////////////////////////////////////////////////////////////////
void main()
{
	Logger* logger = new Logger();
	////////////////////////////////////[ OPEN MP ]////////////////////////////////////////////////
	double start = 0, end = 0;

	omp_set_num_threads(THREAD_NUMBERS);
	start = omp_get_wtime();
	///////////////////////////////////////////////////////////////////////////////////////////////

	Bitmap* original = new Bitmap("./samples/original/nebula-17.bmp");
	Bitmap* negative = original->Clone();
	Bitmap* grayscale = original->Clone();
	Bitmap* gaussiano = original->Clone();
	Bitmap* convolution = original->Clone();

	Effect effect;

	for (size_t i = 0; i <= 5; i++)
	{
		// Uncomment to clone
		//Bitmap* negative = original->Clone();
		//Bitmap* grayscale = original->Clone();

		int thread = pow(2, i);

		printf("Thread number [%d]: \n", thread);
		omp_set_num_threads(thread);

		start = logger->CetCurrentTime();

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

		logger->GetElapsedTime(start);

		// After all save file to hardrive
		//std::string fname_neg = std::string("./samples/negative_") + NumberToString(thread) + std::string(".bmp");
		//negative->Save(fname_neg.c_str());

		//std::string fname_gray = std::string("./samples/grayscale_") + NumberToString(thread) + std::string(".bmp");
		//grayscale->Save(fname_gray.c_str());
	}

	////////////////////////////////////////// EXTRAS /////////////////////////////////////////////
	//start = logger->CetCurrentTime();
	//effect.Negative(*negative);
	//logger->GetElapsedTime(start);

	//// Current filter (SOBEL)
	//start = logger->CetCurrentTime();
	//effect.Convolve(*convolution);
	//logger->GetElapsedTime(start);

	//// Apply 5x times (for fun)
	//start = logger->CetCurrentTime();
	//for (size_t i = 0; i < 50; i++)
	//	effect.Convolve(*gaussiano, gaussian5x5, 1 / 256.f, 0, false);
	//logger->GetElapsedTime(start);

	//original->Save("./samples/original.bmp");
	//convolution->Save("./samples/filter_solber.bmp");
	//gaussiano->Save("./samples/gaussiano.bmp");
	//////////////////////////////////////////////////////////////////////////////////////////////

	negative->Save("./samples/negative.bmp");
	grayscale->Save("./samples/grayscale.bmp");
}