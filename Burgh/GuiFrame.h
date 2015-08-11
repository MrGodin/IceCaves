
#pragma once

#include "GuiObject.h"
class GuiFrame : public GuiObject
{
protected:
	
public:
	void Init();
	struct GuiFrameDesc
	{
		
		long width = 1;
		long height = 1;
		long originX = 0;
		long originY = 0;
		UINT type = GUIOBJECT_UNDEFINED;
		QuadVertexColors baseColor = QVCWhite;
		QuadVertexColors hoverColor = QVCWhite;
		QuadVertexColors outerBorderColor = QVCFrameWhite;
		QuadVertexColors innerBorderColor = QVCFrameGrey;
		IDirect3DTexture9* pTexture = NULL;
		GuiFrameDesc(){};
	};
protected:
	GuiFrameDesc frameDesc;

	DWORD D3DFVF_CUSTOMVERTEX = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;
	DWORD D3DFVF_CUSTOMLINEVERTEX = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
	struct tLineVertex
	{
		float x, y, z;
		float fRHW;
		DWORD color;

	};
	struct tVertex
	{
		float x, y, z;
		float fRHW;
		DWORD color;
		float tu, tv;
	};

	tVertex frame[4];
	tLineVertex lines1[8];
	tLineVertex lines2[8];
	DWORD vert_colors[4];
	RectL hotspot;

	bool PointInFrame(PointL pt)
	{
		return (pt.x > hotspot.left && pt.x < hotspot.right &&
			pt.y > hotspot.top && pt.y < hotspot.bottom);
	}
	static IDirect3DDevice9* pDevice;
	ID3DXFont* pFont = NULL;
	static ID3DXSprite* pSprite;
	HRESULT DrawFrame();
	
public:
	GuiFrame(GuiFrameDesc in_description)
		:
		frameDesc(in_description)
	{
		_type = in_description.type;
		Init();
	}
	long Width(){ return frameDesc.width; }
	void Width(long w){ frameDesc.width = w; }
	long Height(){ return frameDesc.height; }
	long OriginX(){ return frameDesc.originX; }
	long OriginY(){ return frameDesc.originY; }
	
	virtual void SetEnabled(bool v)
	{
		Enabled(v);
		if (Enabled())
			SetToMainColor();
		else
			SetToDisableColor();
	}
	__inline void MoveFrame(long incX,long incY,long maxX,long minX,long maxY,long minY)
	{
		
		frameDesc.originY += incY;
		frameDesc.originX += incX;
		if (frameDesc.originX < minX)
			frameDesc.originX = minX;
		if (frameDesc.originY < minY)
			frameDesc.originY = minY;

		if (frameDesc.originX > maxX)
			frameDesc.originX = maxX;
		if (frameDesc.originY > maxY)
			frameDesc.originY = maxY;
		
		for (int c = 0; c < 4; c++)
		{
			frame[c].x += (float)incX;
			frame[c].y += (float)incY;

			if (frame[c].y < (float)minY)
				frame[c].y = (float)minY;
			if (frame[c].x < (float)minX)
				frame[c].x = (float)minX;

			if (frame[c].y > (float)maxY)
				frame[c].y = (float)maxY;
			if (frame[c].x > (float)maxX)
				frame[c].x = (float)maxX;
		}

		
	}
	__inline void SetToMainColor()
	{
		frame[0].color = frameDesc.baseColor.c0;
		frame[1].color = frameDesc.baseColor.c1;
		frame[2].color = frameDesc.baseColor.c2;
		frame[3].color = frameDesc.baseColor.c3;
	}
	__inline void SetOutterBorder(QuadVertexColors c)
	{
		lines1[0].color = c.c0;
		lines1[1].color = c.c1;
		lines1[2].color = c.c1;
		lines1[3].color = c.c3;

		lines1[4].color = c.c3;
		lines1[5].color = c.c2;
		lines1[6].color = c.c2;
		lines1[7].color = c.c0;

	}
	__inline void SetInnerBorderColor(QuadVertexColors c)
	{

		lines2[0].color = c.c0;
		lines2[1].color = c.c1;
		lines2[2].color = c.c1;
		lines2[3].color = c.c3;

		lines2[4].color = c.c3;
		lines2[5].color = c.c2;
		lines2[6].color = c.c2;
		lines2[7].color = c.c0;
	}
	__inline void SetToDisableColor()
	{
		frame[0].color = QVCDisabled.c0;
		frame[1].color = QVCDisabled.c1;
		frame[2].color = QVCDisabled.c2;
		frame[3].color = QVCDisabled.c3;
	}
	__inline void SetToHoverColor()
	{
		frame[0].color = frameDesc.hoverColor.c0;
		frame[1].color = frameDesc.hoverColor.c1;
		frame[2].color = frameDesc.hoverColor.c2;
		frame[3].color = frameDesc.hoverColor.c3;
	}
	virtual void SetColor(const QuadVertexColors c)
	{
		frame[0].color = c.c0;
		frame[1].color = c.c1;
		frame[2].color = c.c2;
		frame[3].color = c.c3;
	}
	__inline GuiFrameDesc GetFrameDesc()
	{
		return frameDesc;
	}
	__inline static void SetDrawTools(IDirect3DDevice9* device, ID3DXSprite* sprite)
	{
		pDevice = device;
		pSprite = sprite;
	}
	

	__inline HRESULT CreateTexture(WCHAR* fname)
	{
		return D3DXCreateTextureFromFile(pDevice, fname, &frameDesc.pTexture);
	}
	__inline void SetTexture(IDirect3DTexture9* tex){ frameDesc.pTexture = tex; }
	 virtual void SetFont(ID3DXFont* f){ pFont = f; }
	ID3DXFont* GetFont(){ return pFont; }
	virtual HRESULT Rasterize(){return 0;}
	virtual HRESULT OnDeviceLost(){ return 0; }
	virtual HRESULT OnResetDevice(){ return 0; }
	virtual ~GuiFrame()
	{
		if (frameDesc.pTexture)
		{
			SAFE_RELEASE(frameDesc.pTexture);
		}
	};
};

