
#pragma once

#include "GuiFrame.h"
#include "GuiTextControl.h"

class StatDisplay : public GuiFrame
{
private:
	
protected:
	GuiText* pFps = NULL;
	GuiText* pWorldPos = NULL;
public:
	StatDisplay(GuiFrameDesc desc)
		:
		GuiFrame(desc)
	{
	
	}
	~StatDisplay()
	{
		SAFE_DELETE(pFps);
		SAFE_DELETE(pWorldPos);
	}
	void Update(float fps,Vec2F pos)
	{
		TString str = "Fps: ";
		str += TString(fps);
		pFps->SetText(str.w_char());
		str = "Player Pos X :(";
		str += TString(pos.x);
		str += TString(") - Y :(");
		str += TString(pos.y);
		str += TString(")");
		pWorldPos->SetText(str.w_char());
	}
	virtual HRESULT Rasterize()override
	{
		DrawFrame();
		pFps->Rasterize();
		pWorldPos->Rasterize();
		return S_OK;
	}
	void Create()
	{
		GuiFrameDesc fpsDesc;
		fpsDesc.originX = frameDesc.originX + 16;
		fpsDesc.originY = frameDesc.originY + 16;
		pFps = new GuiText(fpsDesc, "What", TEXTALIGN_LEFT);
		pFps->SetColor(Color(255, 0, 255, 0));
		pFps->SetFont(pFont);
		pFps->AlignText();

		fpsDesc.originX = frameDesc.originX + 16;
		fpsDesc.originY = fpsDesc.originY + 18;
		pWorldPos = new GuiText(fpsDesc, "What", TEXTALIGN_LEFT);
		pWorldPos->SetColor(Color(255, 0, 255, 0));
		pWorldPos->SetFont(pFont);
		pWorldPos->AlignText();
		
	}
	void Resize(long x, long y, long w, long h)
	{
		frameDesc.originX = x;
		frameDesc.originY = y;
		frameDesc.width = w;
		frameDesc.height = h;
		Init();
		SAFE_DELETE(pFps);
		SAFE_DELETE(pWorldPos);
		Create();
	}
};