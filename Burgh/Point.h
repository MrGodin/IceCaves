
#pragma once

#include "windows.h"

template <typename T>
class _Point
{
public:
	T x;
	T y;
	_Point(T inX, T inY)
		:
		x(inX),
		y(inY)
	{

	}
};

typedef _Point <long> PointL;
typedef _Point<int> PointI;
typedef _Point<float> PointF;
