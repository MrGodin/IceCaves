
#pragma once

#include "windows.h"

template <class T>
class _Rect
{
public:
	T top;
	T left;
	T right;
	T bottom;
public:
	_Rect()
	{
		left = 0;
		right = 0;
		top = 0;
		bottom = 0;
	}
	_Rect(T top, T left, T right, T bottom)
		:
		top(top),
		left(left),
		right(right),
		bottom(bottom)
	{}
	_Rect(_Rect& r)
		:
		top(r.top),
		left(r.left),
		right(r.right),
		bottom(r.bottom)
	{}
	
	void SetRectR(RECT r)
	{

		bottom = (T)r.bottom;
		left = (T)r.left;
		right = (T)r.right;
		top = (T)r.top;

	}
	void Translate(T x, T y)
	{

		left += x;
		right += x;
		top += y;
		bottom += y;
	}
	void Draw(ID3DXLine* line)
	{
		D3DXVECTOR2 pts[8];
		pts[0] = D3DXVECTOR2(left, top);
		pts[1] = D3DXVECTOR2(right, top);
		pts[2] = D3DXVECTOR2(right, top);
		pts[3] = D3DXVECTOR2(right, bottom);
		pts[4] = D3DXVECTOR2(right, bottom);
		pts[5] = D3DXVECTOR2(left, bottom);
		pts[6] = D3DXVECTOR2(left, bottom);
		pts[7] = D3DXVECTOR2(left, top);
		line->Draw(pts, 8, 0xffffffff);
	}
	RECT ToRECT()
	{
		RECT r;
		r.top = (long)top;
		r.left = (long)left;
		r.right = (long)right;
		r.bottom = (long)bottom;
		return r;
	}
	void ClipTo(_Rect<int> rect)
	{
		left = __max(left, rect.left);
		top = __max(top, rect.top);
		right = __min(right, rect.right);
		bottom = __min(bottom, rect.bottom);
	}
	inline bool OverLaps(Rect& rect)
	{
		return top < rect.bottom && bottom > rect.top && left < rect.right && right > rect.left;
	}

	inline bool Conatins(Vec2& pt)
	{
		return pt.x >= left && pt.x <= right && pt.y >= top && pt.y <= bottom;
	}
	template <class T2>
	operator _Rect< T2 >() const
	{
		return _Rect<int>((T2)top, (T2)left, (T2)right, (T2)bottom);
	}

};

typedef _Rect< float > RectF;
typedef _Rect< int > RectI;
typedef _Rect< long > RectL;