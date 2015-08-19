
#include "GuiCheckBox.h"

bool GuiCheckBox::OnMouseMove(GuiEvent& Event)
{
	return false;
}

bool GuiCheckBox::OnMouseClick(GuiEvent& Event)
{
	if (Event.Msg == WM_LBUTTONDOWN && PointInFrame({ Event.Mouse.x, Event.Mouse.y }))
	{
		checked = !checked;
		if (checked)
			pBox->SetColor(QVCGreen);
		else
			pBox->SetColor(QVCWhite);
		Event.Sender = this;
		Event.Action = this->Action();
		return true;
	}
	
	return false;
}
HRESULT GuiCheckBox::Rasterize()
{
	DrawFrame();
	pBox->Rasterize();
	if (checked)
		pFont->DrawText(pSprite, checkText.w_char(), 1, &drawTextRect, drawFlag, checkTextColor);

	    pFont->DrawText(pSprite, caption.w_char(), wcslen(caption.w_char()), &captionRect, drawFlag, captionColor);

	return 0;
}