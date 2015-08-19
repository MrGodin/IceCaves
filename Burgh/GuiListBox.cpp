
#include "GuiListBox.h"
bool GuiListItem::OnMouseMove(GuiEvent& Event)
{
	// create a thin line around the border
	if (PointInFrame({ Event.Mouse.x, Event.Mouse.y }))
	{
		SetInnerBorderColor(QVCFrameGrey);
		return true;
	}
	else
	{
		SetInnerBorderColor(QVCTransparent);
	}
	return false;
};
bool GuiListItem::OnMouseClick(GuiEvent& Event)
{
	
	
	
	if ( PointInFrame({ Event.Mouse.x, Event.Mouse.y }))
	{
		Event.Sender = this;
		selected = true;
		Event.Captured = true;
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
	if (strList.size() < 1)
		return false;
	for (UINT i = 0; i < children.size(); i++)
	{
		GuiObject* obj = children[i];
		switch (obj->Type())
		{
		case GUIOBJECT_SLIDER:
		{
			GuiSlider* sl = (GuiSlider*)obj;
			sl->OnMouseMove(Event);
			break;
		}
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
	
	if (strList.size() < 1)
		return false;
	if (PointInFrame({ Event.Mouse.x, Event.Mouse.y }))
	{
		for (UINT i = 0; i < children.size(); i++)
		{
			GuiObject* obj = children[i];
			switch (obj->Type())
			{
			case GUIOBJECT_SLIDER:
			{
				GuiSlider* sl = (GuiSlider*)obj;
				if (sl->OnMouseClick(Event))
				{
					if (pSelectedItem)
					{
						pSelectedItem->SetSelected(false);
						pSelectedItem = NULL;
					}
				}
				break;
			}
			case GUIOBJECT_LISTBOX_ITEM:
			{
				GuiListItem* item = (GuiListItem*)obj;
				UINT len = wcslen(item->GetText().w_char());
				if (len > 0 && item != pSelectedItem)
				{
					if (item->OnMouseClick(Event))
					{
						if (pSelectedItem)
							pSelectedItem->SetSelected(false);

						pSelectedItem = (GuiListItem*)Event.Sender;

					}
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
	for (UINT i = 0; i < children.size(); i++)
	{
		GuiFrame* obj = (GuiFrame*)children[i];
		obj->Rasterize();
	}
	return S_OK;
}