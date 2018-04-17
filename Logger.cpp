#include "Logger.h"

Logger::Logger() {}

Logger::~Logger() {}

double Logger::CetCurrentTime() 
{
	return omp_get_wtime();
}
void Logger::GetElapsedTime(double startTime)
{
	printf_s("Elapsed time: %f seconds \n", omp_get_wtime() - startTime);
}

void Logger::PrintThreadForIteraction(int x, int y)
{
	printf_s("[i,j]: Thread %d executa a iteração [%d, %d] do loop. \n", omp_get_thread_num(), x, y);
}
