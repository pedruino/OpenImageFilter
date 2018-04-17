#include <omp.h>
#include "Bitmap.h"
#include "Effect.h"

////////////////////////////////////[ OPEN MP ]/////////////////////////////////////
#undef DEBUG
#include "Logger.h"
#define THREAD_NUMBERS 1
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
	Bitmap* convolution = original->Clone();

	Effect effect;

	start = logger->CetCurrentTime();
	effect.Negative(*negative);
	logger->GetElapsedTime(start);

	////////////////////////////////////////// EXTRAS /////////////////////////////////////////////
	effect.Grayscale(*grayscale);
	start = logger->CetCurrentTime();
	logger->GetElapsedTime(start);

	start = logger->CetCurrentTime();
	effect.Blur(*convolution);
	logger->GetElapsedTime(start);

	effect.Blur(*convolution);
	effect.Blur(*convolution);
	effect.Blur(*convolution);

	logger->GetElapsedTime(start);

	original->Save("./samples/original2.bmp");
	negative->Save("./samples/negative2.bmp");
	grayscale->Save("./samples/grayscale.bmp");
	convolution->Save("./samples/convolution2.bmp");
}