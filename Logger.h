#pragma once
#include <stdio.h>
#include <omp.h>

class Logger
{
public:
	Logger();
	~Logger();
	double CetCurrentTime();
	void GetElapsedTime(double startTime);
	static void PrintThreadForIteraction(int x, int y);
};

