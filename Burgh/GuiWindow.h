
#pragma once


#include "GuiButton.h"
#include "GuiContainer.h"


class GuiWindow : public GuiControl
{
public:
	
protected:
	UINT numbChildren = 0;
	
public:
	GuiWindow(GuiFrameDesc d,UINT nChildren)
		:
	GuiControl(d),
	numbChildren(nChildren)
	{
		
	}
	Vec2L Origin(){ return Vec2L(frameDesc.originX, frameDesc.originY); }
	virtual ~GuiWindow(){}
	virtual bool OnMouseMove(GuiEvent& Event)override;
	virtual bool OnMouseClick(GuiEvent& Event)override;
	virtual HRESULT Rasterize()override;
	
};