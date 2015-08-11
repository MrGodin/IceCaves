
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
		if (itemCount > Desc.itemDisplayCount)
		{
			float percent = (float)(Desc.itemDisplayCount / itemCount);
			frameDesc.height = (long)(parentHeight * percent);
			float move_space = (float)parentHeight - frameDesc.height;
			int undisplayeditems = (int)(itemCount- Desc.itemDisplayCount);
		    moveDistToIndex = move_space / undisplayeditems;
			
		}
		else
		{
			frameDesc.height = obj->Height();
		}
		Init();

	}
	UINT CurrentIndex(){ return (UINT)currIndex; }
	virtual bool OnMouseMove(GuiEvent& Event);
	virtual bool OnMouseClick(GuiEvent& Event);
	virtual HRESULT Rasterize();
};