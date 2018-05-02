//
// Created by pedruino on 5/1/18.
//
#include <omp.h>
#include <cstdio>
#include "Logger.h"

Logger::Logger() {}

Logger::~Logger() {}

double Logger::CetCurrentTime()
{
    return omp_get_wtime();
}
void Logger::GetElapsedTime(double startTime)
{
    printf("Elapsed time: %f seconds \n", omp_get_wtime() - startTime);
}

void Logger::PrintThreadForIteraction(int x, int y)
{
    printf("[i,j]: Thread %d executa a itera��o [%d, %d] do loop. \n", omp_get_thread_num(), x, y);
}

void Logger::PrintCurrentThread()
{
    printf("Running on thread %d\n", omp_get_thread_num());
}