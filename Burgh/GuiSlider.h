
#pragma once

#include "GuiControl.h"
#include "GuiSliderKnob.h"

class GuiSlider : public GuiControl
{
public:
	__inline void CreateKnob(GuiSliderKnob::GuiSliderKnobDesc knobDesc)
	{
	
		AddChild(new GuiSliderKnob(knobDesc));
	}
protected:
	GuiSliderKnob* pKnob = NULL;
public:
	GuiSlider(GuiFrameDesc desc)
		:
		GuiControl(desc)
	{

	}
	
	virtual HRESULT Rasterize()override;
	virtual bool OnMouseClick(GuiEvent& Event)override;
	virtual bool OnMouseMove(GuiEvent& Event)override;

};