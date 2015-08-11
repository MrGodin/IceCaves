
#pragma once

#include "GuiTextControl.h"

class GuiButton : public GuiControl
{


public:
	struct GuiButtonDesc
	{
		GuiFrameDesc frameDesc;
		UINT Action;
		UINT Index;
		WCHAR* Text = '\0';
		UINT txtAlign = 2;//left
		UINT clientAlign = GuiClientAlignLeft;
	};
protected:
	GuiButtonDesc Desc;
	GuiText* pCaptionText = NULL;
public:
	
public:
	GuiButton(GuiButtonDesc desc)
	  :
	GuiControl(desc.frameDesc),
	Desc(desc)
	{
		pCaptionText = new GuiText(Desc.frameDesc, Desc.Text, Desc.txtAlign);
		
	}
	virtual ~GuiButton()
	{
		SAFE_DELETE(pCaptionText);
	}
	UINT GetAction(){ return Desc.Action; }
	
	virtual void SetFont(ID3DXFont* f)override
	{
		pFont = f;
		pCaptionText->SetFont(pFont);
		pCaptionText->AlignText();
		pCaptionText->SetColor(Color(255, 0, 255, 0));
	}
	 bool Enabled()override{ return _enabled; }
	 void Enabled(bool v)override
	{
		_enabled = v;
		if (!_enabled)
		{
			SetToDisableColor();
		}
		else
		{
			SetToMainColor();
		}
	}
	virtual HRESULT Rasterize()override;
	virtual bool OnMouseMove(GuiEvent& Event)override;
	virtual bool OnMouseClick(GuiEvent& Event)override;
};