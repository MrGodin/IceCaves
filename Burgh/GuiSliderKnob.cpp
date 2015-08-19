
#include "GuiSliderKnob.h"
#include "GuiListBox.h"

bool GuiSliderKnob::OnMouseMove(GuiEvent& Event)
{
	if (mouse_captured )
	{
		static float Y = (float)Event.Mouse.y;
		GuiFrame* obj = (GuiFrame*)_parent;
		float resultY = Y - Event.Mouse.y;
		
		MoveFrame(0.0f,
			-resultY,
			frameDesc.originX,
			frameDesc.originX,
			(obj->OriginY() + obj->Height()) - frameDesc.height,
			obj->OriginY());
		
		UINT index = (float)(frameDesc.originY - obj->OriginY()) / moveDistToIndex;
		GuiListBox* lb = (GuiListBox*)obj->Owner();
		if (lb)
		{
			 lb->UpdateStrings(index);
		}
		Y = (float)Event.Mouse.y;
		return true;
		
	}
	return false;
};
bool GuiSliderKnob::OnMouseClick(GuiEvent& Event)
{
	if (Event.Msg = WM_LBUTTONDOWN && PointInFrame({ Event.Mouse.x, Event.Mouse.y }))
	{
		//set static mouse capture
		GuiControl::SetMouseCapture(true);
		// get click pos of mouse
		clickPos = Vec2L(Event.Mouse.x, Event.Mouse.y);
		return true;
	}
	return false;
}
HRESULT GuiSliderKnob::Rasterize()
{
	DrawFrame();
	return S_OK;
};