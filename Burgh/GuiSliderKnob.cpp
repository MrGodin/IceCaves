
#include "GuiSliderKnob.h"

bool GuiSliderKnob::OnMouseMove(GuiEvent& Event)
{
	if (mouse_captured )
	{
		GuiFrame* obj = (GuiFrame*)_parent;
		float resultY = clickPos.y - Event.Mouse.y;
		
		MoveFrame(0.0f,
			-resultY,
			frameDesc.originX,
			frameDesc.originX,
			(obj->OriginY() + obj->Height()) - frameDesc.height,
			obj->OriginY());

		float len = obj->OriginY() - frameDesc.originY;
		int   index = len / moveDistToIndex;
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
	return S_OK;
};