#pragma once
#ifndef KERNELS_H
#define KERNELS_H
#include <array>

template<class T, size_t Rows, size_t Cols> using matrix = std::array<std::array<T, Cols>, Rows>;

// Sobel
const double sobelx[][3]
{
	{ -1, 0, 1 },
	{ -2, 0, 2 },
	{ -1, 0, 1 }
};
const double sobely[][3]
{
	{ 1,  2,  1 },
	{ 0,  0,  0 },
	{ -1, -2, -1 }
};

// Prewitt
const double prewittx[][3]
{
	{ -1, 0, 1 },
	{ -1, 0, 1 },
	{ -1, 0, 1 }
};
const double prewitty[][3]
{
	 { -1, -1, -1 },
	 { 0,  0,   0 },
	 { 1,  1,   1 }
};

// Roberts
const double robertsx[][2]
{
	{ 1,  0 },
	{ 0, -1 }
};

const double robertsy[][2]
{
	{ 0, 1 },
	{ -1, 0 }
};

// Scharr
const double scharrx[][3]
{
	{  3,  10,  3 },
	{  0,   0,  0 },
	{ -3, -10, -3 }
};
const double scharry[][3]
{
	{  3, 0,  -3 },
	{ 10, 0, -10 },
	{  3, 0,  -3 }
};

const double laplacian5x5[][5] =
{
	{ -1, -1, -1, -1, -1, },
	{ -1, -1, -1, -1, -1, },
	{ -1, -1, 24, -1, -1, },
	{ -1, -1, -1, -1, -1, },
	{ -1, -1, -1, -1, -1 }
};

const double gaussian5x5[][5] =
{
	{ 1,   4,  6,  4,  1 },
	{ 4,  16, 24, 16,  4 },
	{ 6,  24, 36, 24,  6 },
	{ 4,  16, 24, 16,  4 },
	{ 1,   4,  6,  4,  1 }
};

#endif // KERNELS_H