
#include "GuiDisplayPanel.h"


void GuiDisplayPanel::Create()
{
	float X = (float)frameDesc.originX;
	float Y = (float)frameDesc.originY;
	float itemWidth = (float)frameDesc.width / (float)Desc.cols;
	GuiFrameDesc iDesc;
	iDesc.width = (UINT)itemWidth;
	iDesc.height = (UINT)Desc.itemHeight;
	iDesc.baseColor = iDesc.hoverColor = iDesc.innerBorderColor = iDesc.outerBorderColor = QVCTransparent;

	iDesc.type = GUIOBJECT_LISTBOX_ITEM;

	for (UINT y = 0; y < Desc.rows; y++)
	{
		for (UINT x = 0; x < Desc.cols; x++)
		{
			const UINT index = y * Desc.cols + x;
			
			iDesc.originX = X;
			iDesc.originY = Y;
			GuiListItem* Item = new GuiListItem(iDesc);
			Item->SetFont(pFont);
			
			
			AddChild(Item);
			X += itemWidth;
		}
		Y += Desc.itemHeight;
		X = frameDesc.originX;
	}
}
HRESULT GuiDisplayPanel::Rasterize()
{
	DrawFrame();
	for (UINT c = 0; c < children.size(); c++)
	{
		GuiFrame* frm = (GuiFrame*)children[c];
		if (frm)
		{
			frm->Rasterize();
		}
	}
	return S_OK;
};
bool GuiDisplayPanel::OnMouseMove(GuiEvent& Event)
{
	for (UINT c = 0; c < children.size(); c++)
	{
		GuiListItem* control = (GuiListItem*)children[c];
		if (control)
		{
			control->OnMouseMove(Event);
		}
	}
	return false;
};
bool GuiDisplayPanel::OnMouseClick(GuiEvent& Event)
{
	return false;
};