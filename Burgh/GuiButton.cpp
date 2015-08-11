
#include "GuiButton.h"

HRESULT GuiButton::Rasterize()
{
	if (Visible())
	{
		if (SUCCEEDED(DrawFrame()))
			return pCaptionText->Rasterize();
		else
			return E_FAIL;
	}
	return S_OK;
}
bool GuiButton::OnMouseMove(GuiEvent& Event)
{
	if (!Visible() || !Enabled())
		return false;

	if (Enabled())
	{
		if (PointInFrame({ Event.Mouse.x, Event.Mouse.y }))
		{
			SetToHoverColor();
			return true;
		}
		else
		{
			SetToMainColor();
		}
	}
	return false;
}
bool GuiButton::OnMouseClick(GuiEvent& Event)
{
	if (!Visible() || !Enabled())
		return false;
	
	if (Enabled() && Visible())
	{
		if (Event.Msg == WM_LBUTTONDOWN && PointInFrame({ Event.Mouse.x, Event.Mouse.y }))
		{
			Event.Event = GuiEvent_Capture;
			Event.Action = Desc.Action;
			Event.Sender = this;
			return true;
		}
		else
		{
			Event.Event = GuiEvent_None;
			Event.Action = 0;

		}
	}
	return false;
}