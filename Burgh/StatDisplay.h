
#pragma once

#include "GuiFrame.h"
#include "GuiTextControl.h"

class StatDisplay : public GuiFrame
{
private:
	
protected:
	GuiText* pFps = NULL;
	GuiText* pWorldPos = NULL;
	GuiText* pGameTime = NULL;
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
		SAFE_DELETE(pGameTime);
	}
	void Update(float fps,int cpu,Vec2F pos,float gt)
	{
		TString str = "Performance :-> Fps: ";
		str += TString(fps);
		str += TString(" <-> Cpu: ");
		str += TString(cpu);
		str += TString("%");
		pFps->SetText(str.w_char());
		str = "Player Pos X :(";
		str += TString(pos.x);
		str += TString(") - Y :(");
		str += TString(pos.y);
		str += TString(")");
		
		pWorldPos->SetText(str.w_char());

		str = "Game Time : ";
		str += TString(gt);
		pGameTime->SetText(str.w_char());
	}
	virtual HRESULT Rasterize()override
	{
		DrawFrame();
		pFps->Rasterize();
		pWorldPos->Rasterize();
		pGameTime->Rasterize();
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
		fpsDesc.originY = fpsDesc.originY + 16;
		pWorldPos = new GuiText(fpsDesc, "What", TEXTALIGN_LEFT);
		pWorldPos->SetColor(Color(255, 0, 255, 0));
		pWorldPos->SetFont(pFont);
		pWorldPos->AlignText();

		fpsDesc.originX = frameDesc.originX + 16;
		fpsDesc.originY = fpsDesc.originY + 16;
		pGameTime = new GuiText(fpsDesc, "What", TEXTALIGN_LEFT);
		pGameTime->SetColor(Color(255, 0, 255, 0));
		pGameTime->SetFont(pFont);
		pGameTime->AlignText();
		
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
		SAFE_DELETE(pGameTime);
		Create();
	}
};