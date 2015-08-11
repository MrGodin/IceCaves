#pragma once

#include "Utils.h"
template<typename T>
class _Grid
{
private:
	T iWidth;
	T iHeight;
	T iClipSize;
	T iRows;
	T iCols;
	T iRectCount;

public:
	_Grid(){};
	_Grid(T width, T height, T clipsize)
		:
		iWidth(width),
		iHeight(height),
		iClipSize(clipsize)
	{
		iRows = iHeight / iClipSize;
		iCols = iWidth / iClipSize;
		iRectCount = iRows * iCols;
	};
	~_Grid()
	{

	}
	T RowCount(){ return iRows; }
	T ColCount(){ return iCols; }
	T SectorCount(){ return iRectCount; };

	RECT* GetRectFace(T faceX, T faceY)
	{
		T col = faceX / iClipSize;
		T row = faceY / iClipSize;
		T index = row * iCols + col;
		return GetRect(index);
	}

	RECT   GetRect(T in_row, T in_col)
	{
		T index = in_row * iCols + in_col;
		return GetRect(index);
	}
	RECT  GetRect(T index)
	{
		RECT r;
		r.top = r.right = r.left = r.bottom = -1;
		if (index >= iRectCount)
			return r;

		LONG resultDiv = (LONG)index / (LONG)iCols;
		LONG resultMod = (LONG)index % (LONG)iCols;
		LONG x = resultMod * (LONG)iClipSize;
		LONG y = resultDiv * (LONG)iClipSize;

		r.left = x;
		r.top = y;
		r.bottom = y + (LONG)iClipSize;
		r.right = x + (LONG)iClipSize;
		return r;
	}
	void Create(T width, T height, T clipsize)
	{

		iHeight = height;
		iWidth = width;
		iClipSize = clipsize;
		iRows = iHeight / iClipSize;
		iCols = iWidth / iClipSize;
		iRectCount = iRows * iCols;

	}

};

typedef _Grid< int > GridI;
typedef _Grid< float > GridF;