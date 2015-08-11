
#pragma once 
#include "Utils.h"

#include "Viewport2.h"
class Camera
{
private:
	
	Viewport& port;
	float x;
	float y;
	RectF Box;


public:

	Camera(Viewport& port)
		:
		port(port)
	{
		SetPosition(port.GetWidth() / 2.0f, port.GetHeight() / 2.0f);
	}
	void SetBindingBox(RectF& b){ Box = b; };
	D3DXVECTOR3 GetPos(){ return D3DXVECTOR3((float)port.GetX(), (float)port.GetY(), 0.0f); }
	V2 ScreenPos()
	{
		return V2(x, y);
	}
	void SetPosition(float nx, float ny)
	{
		x = nx - (port.GetWidth()/ 2.0f);
		y = ny - port.GetHeight() / 2.0f;
		x = __max(x, Box.left);
		y = __max(y, Box.top);
		x = __min(x, Box.right - port.GetWidth());
		y = __min(y, Box.bottom - port.GetHeight());
	}
};