
#include "GuiListBox.h"
bool GuiListItem::OnMouseMove(GuiEvent& Event)
{
	// create a thin line around the border
	if (PointInFrame({ Event.Mouse.x, Event.Mouse.y }))
	{
		SetInnerBorderColor(QVCFrameGrey);
	}
	else
	{
		SetInnerBorderColor(QVCTransparent);
	}
	return false;
};
bool GuiListItem::OnMouseClick(GuiEvent& Event)
{
	if (Event.Msg == WM_LBUTTONDOWN && PointInFrame({ Event.Mouse.x, Event.Mouse.y }))
	{
		Event.Sender = this;
		selected = true;
		return true;
	}
	else
	{
		selected = false;
	}
	
	return false;
}
HRESULT GuiListItem::Rasterize()
{
	if (selected)
		SetColor(QVCBlueHover);
	else
		SetColor(QVCTransparent);

	DrawFrame();
	pText->Rasterize();
	return S_OK;
}

///////////////////////////////////////////////////////////////
// ListBox
///////////////////////////////////////////////////////////////

bool GuiListBox::OnMouseMove(GuiEvent& Event)
{
	for (UINT i = 0; i < children.size(); i++)
	{
		GuiObject* obj = children[i];
		switch (obj->Type())
		{
		case GUIOBJECT_LISTBOX_ITEM:
		{
			GuiListItem* item = (GuiListItem*)obj;
			item->OnMouseMove(Event);
		}
		break;
		default:
			break;
		}
	}
	return false;
};
bool GuiListBox::OnMouseClick(GuiEvent& Event)
{
	if (PointInFrame({ Event.Mouse.x, Event.Mouse.y }))
	{
		for (UINT i = 0; i < children.size(); i++)
		{
			GuiObject* obj = children[i];
			switch (obj->Type())
			{
			case GUIOBJECT_LISTBOX_ITEM:
			{
				GuiListItem* item = (GuiListItem*)obj;
				if (item->OnMouseClick(Event))
				{
					pSelectedItem = (GuiListItem*)Event.Sender;
					
					return true;
				}
			}
			break;
			default:
				
				break;
			}
		}
		Event.Sender = this;
		return true;
	}
	return false;
}
HRESULT GuiListBox::Rasterize()
{
	
	DrawFrame();
	
	return S_OK;
}