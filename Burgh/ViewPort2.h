
#pragma once

#include "Utils.h"

class Viewport
{
protected:
	D3DVIEWPORT9 Data;
	IDirect3DDevice9* pDevice = NULL;
public:
	Viewport(DWORD X,DWORD Y,DWORD w,DWORD h)
	{
		Data.X = X;
		Data.Y = Y;
		Data.Width = w;
		Data.Height = h;
		Data.MinZ = 0.0f;
		Data.MaxZ = 1.0f;
	}
	void SetDevice(IDirect3DDevice9* dev){ pDevice = dev; }
	void Reset(const RectL rect)
	{
		Data.X = (DWORD)rect.left;
		Data.Y = (DWORD)rect.top;
		Data.Width = (DWORD)(rect.right - rect.left);
		Data.Height = (DWORD)(rect.bottom - rect.top);
		
		Data.MinZ = 0.0f;
		Data.MaxZ = 1.0f;
		pDevice->SetViewport(&Data);
	}
	void ResetCenter(long scrnW,long scrnH,long w,long h)
	{
		Data.Width = (DWORD)w;
		Data.Height = (DWORD)h;
		Data.X = (DWORD)((scrnW / 2) - (w / 2));
		Data.Y = (DWORD)((scrnH / 2) - (h / 2));
		Data.MinZ = 0.0f;
		Data.MaxZ = 1.0f;
		pDevice->SetViewport(&Data);
	};
	DWORD GetX(){ return Data.X; }
	DWORD GetY(){ return Data.Y; }
	DWORD GetHeight(){ return Data.Height; }
	DWORD GetWidth(){ return Data.Width; }

};