
#pragma once

#include "GuiTextControl.h"
#include "GuiControl.h"

class GuiInputBox : public GuiControl
{
protected:
	GuiText* pText = NULL;
	TString text;
public:
	GuiInputBox(GuiFrameDesc desc)
		:
		GuiControl(desc)
		//GuiText(desc, L"", TEXTALIGN_LEFT, 16)
	{

	}
	virtual HRESULT Rasterize()override;
	virtual bool OnKeyPress(GuiControl::GuiEvent& Event)override;
	TString GetText()
	{
		TString str = text;
		str.Trim();
		return str;
	}
	void Create();
	static TString GetChar(WPARAM key);
};