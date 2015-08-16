

#include "GuiSlider.h"


HRESULT  GuiSlider::Rasterize()
{
	DrawFrame();
	for (UINT i = 0; i < children.size(); i++)
	{
		GuiObject* obj = children[i];
		switch (obj->Type())
		{
		case GUIOBJECT_KNOB:
		{
			GuiSliderKnob* knob = (GuiSliderKnob*)obj;
			knob->Rasterize();

			break;
		}
		default:
			break;
		}
	}
	return S_OK;
}

bool GuiSlider::OnMouseMove(GuiEvent& Event)
{
	for (UINT i = 0; i < children.size(); i++)
	{
		GuiObject* obj = children[i];
		switch (obj->Type())
		{
		case GUIOBJECT_KNOB:
		{
			GuiSliderKnob* knob = (GuiSliderKnob*)obj;
			knob->OnMouseMove(Event);
			
			break;
		}
		default:
			break;
		}
	}
	return false;
}
bool GuiSlider::OnMouseClick(GuiEvent& Event)
{
	for (UINT i = 0; i < children.size(); i++)
	{
		GuiObject* obj = children[i];
		switch (obj->Type())
		{
		case GUIOBJECT_KNOB:
		{
			GuiSliderKnob* knob = (GuiSliderKnob*)obj;
			return knob->OnMouseClick(Event);
			
		}
		default:
			break;
		}
	}
	return false;
}