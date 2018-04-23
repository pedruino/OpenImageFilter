#include <omp.h>
#include "Bitmap.h"
#include "Effect.h"
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

	Bitmap* original = new Bitmap("./samples/original/profileimage.bmp");
	Bitmap* negative = original->Clone();
	Bitmap* grayscale = original->Clone();
	Bitmap* gaussiano = original->Clone();
	Bitmap* convolution = original->Clone();

	Effect effect;

	start = logger->CetCurrentTime();
	effect.Negative(*negative);
	logger->GetElapsedTime(start);

	////////////////////////////////////////// EXTRAS /////////////////////////////////////////////
	start = logger->CetCurrentTime();
	effect.Grayscale(*grayscale);
	logger->GetElapsedTime(start);

	// Current filter (SOBEL)
	start = logger->CetCurrentTime();
	effect.Convolve(*convolution);
	logger->GetElapsedTime(start);

	// Apply 5x times (for fun)
	start = logger->CetCurrentTime();
	for (size_t i = 0; i < 50; i++)
		effect.Convolve(*gaussiano, gaussian5x5, 1 / 256.f, 0, false);
	logger->GetElapsedTime(start);

	original->Save("./samples/original.bmp");
	negative->Save("./samples/negative.bmp");
	grayscale->Save("./samples/grayscale.bmp");
	gaussiano->Save("./samples/gaussiano.bmp");
	convolution->Save("./samples/filter_solber.bmp");
}