
#pragma once

#include "GuiControl.h"
#include "GuiTextControl.h"
class GuiCheckBox : public GuiControl
{
protected:
	TString checkText = "X";
	TString caption;
	DWORD checkTextColor = Color(255, 0,0,0);
	DWORD captionColor = Color(255, 255, 255, 255);
	RECT drawTextRect;
	RECT captionRect;
	DWORD drawFlag = DT_LEFT | DT_NOCLIP;
	GuiControl* pBox = NULL;
	bool checked = false;
	UINT action;
public:
	void Create()
	{
		GuiFrameDesc boxDesc;
		boxDesc.originX = frameDesc.originX + 1;
		boxDesc.originY = frameDesc.originY + 1;
		boxDesc.width = 16;
		boxDesc.height = frameDesc.height - 2;
		boxDesc.innerBorderColor = QVCBlue;
		boxDesc.outerBorderColor = QVCFrameGrey;
		boxDesc.baseColor = QVCWhite;
		drawTextRect.left = boxDesc.originX+ 4;
		drawTextRect.top = boxDesc.originY;
		captionRect.left = boxDesc.originX + (boxDesc.width + 4);
		captionRect.top = boxDesc.originY;
		pBox = new GuiControl(boxDesc);
		pBox->SetFont(pFont);


		
	}
public:
	GuiCheckBox(GuiFrameDesc desc,UINT in_action)
		:
		GuiControl(desc),
		action(in_action)
	{
		
	}
	~GuiCheckBox()
	{
		SAFE_DELETE(pBox);
	}
	bool Checked(){ return checked; }
	void Checked(bool val)
	{ 
		checked = val; 
		if (checked)
			pBox->SetColor(QVCGreen);
		else
			pBox->SetColor(QVCWhite);
	}
	UINT Action(){ return action; }
	void SetCaption(TString capt){ caption = capt; }
	virtual bool OnMouseClick(GuiEvent& Event)override;
	virtual bool OnMouseMove(GuiEvent& Event)override;
	virtual HRESULT Rasterize()override;
};