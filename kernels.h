#pragma once
#ifndef KERNELS_H
#define KERNELS_H
#include <array>

template<class T, size_t Rows, size_t Cols> using matrix = std::array<std::array<T, Cols>, Rows>;

const matrix<int, 3, 3> sobelx{ { { { -1, 0, 1 } },{ { -2, 0, 2 } },{ { -1, 0, 1 } } } };
const matrix<int, 3, 3> sobely{ { { { 1, 2, 1 } },{ { 0, 0, 0 } },{ { -1, -2, -1 } } } };
const matrix<int, 3, 3> prewittx{ { { { -1, 0, 1 } },{ { -1, 0, 1 } },{ { -1, 0, 1 } } } };
const matrix<int, 3, 3> prewitty{ { { { -1, -1, -1 } },{ { 0, 0, 0 } },{ { 1, 1, 1 } } } };
const matrix<int, 2, 2> robertsx{ { { { 1, 0 } },{ { 0, -1 } } } };
const matrix<int, 2, 2> robertsy{ { { { 0, 1 } },{ { -1, 0 } } } };
const matrix<int, 3, 3> scharrx{ { { { 3, 10, 3 } },{ { 0, 0, 0 } },{ { -3, -10, -3 } } } };
const matrix<int, 3, 3> scharry{ { { { 3, 0, -3 } },{ { 10, 0, -10 } },{ { 3, 0, -3 } } } };

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

