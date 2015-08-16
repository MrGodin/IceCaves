
#pragma once

#include "GuiControl.h"

class GuiSliderKnob : public GuiControl
{
protected:
	Vec2L clickPos;
	float moveDistToIndex = 0.0f;
	int currIndex = 0;
public:
	struct GuiSliderKnobDesc
	{
		UINT maxItems;
		UINT minHeight;
		UINT itemDisplayCount;
		GuiFrameDesc frmDesc;
	};
	struct KnobData
	{
		
	};
protected:
	GuiSliderKnobDesc Desc;
public:
	GuiSliderKnob(GuiSliderKnobDesc desc)
		:
		GuiControl(desc.frmDesc),
		Desc(desc)
	{

	}
	void Resize(UINT itemCount)
	{
		

		GuiFrame* obj = (GuiFrame*)_parent;
		float parentHeight = (float)obj->Height();

		UINT itemsNotDisplayed = itemCount - Desc.itemDisplayCount;
		float per = (float)Desc.itemDisplayCount / (float)itemCount;
		frameDesc.height = (long)(parentHeight * per);
		float distToMove = parentHeight - frameDesc.height;
		moveDistToIndex = distToMove / itemsNotDisplayed;
		Init();

	}
	UINT CurrentIndex(){ return (UINT)currIndex; }
	virtual bool OnMouseMove(GuiEvent& Event);
	virtual bool OnMouseClick(GuiEvent& Event);
	virtual HRESULT Rasterize();
};