
#include "GuiWindow.h"
#include "GuiListBox.h"
#include "GuiCheckBox.h"
#include "GuiDisplayPanel.h"
#include "GuiInputBox.h"
#include "Engine.h"



HRESULT GuiWindow::Rasterize()
{
	DrawFrame();
	for (UINT c = 0; c < children.size(); c++)
	{
		GuiFrame* frm = (GuiFrame*)GetChild(c);
		if (frm)
			frm->Rasterize();
	}
	return S_OK;
}
bool GuiWindow::OnMouseMove(GuiEvent& Event)
{
	for (UINT i = 0; i < children.size(); i++)
	{
		GuiObject* obj = GetChild(i);
		if (!obj)
			continue;

		switch (obj->Type())
		{
		case GUIOBJECT_BUTTON:
		{
			GuiButton* btn = NULL;
			try	{ btn = (GuiButton*)obj; }
			catch (...)	{ btn = NULL; }
			if (btn)
			{
				if (btn->OnMouseMove(Event))
				{
					Event.Sender = btn;
					return true;
				};
			}
			
		}
		break;
		case GUIOBJECT_LISTBOX:
		{
			GuiListBox* LB = (GuiListBox*)obj;
			if (LB)
				LB->OnMouseMove(Event);

		}
		case GUIOBJECT_BTNCONTAINER:
		{
			GuiButtonContainer* BtnC = (GuiButtonContainer*)obj;
			if (BtnC)
			   if(BtnC->OnMouseMove(Event))
				   return true;
		
		}
		break;
		case GUIOBJECT_DISPLAYPANEL:
		{
			GuiDisplayPanel* panel = (GuiDisplayPanel*)obj;
			if (panel)
				panel->OnMouseMove(Event);

		}
		break;
		}

	}

	return false;
}

bool GuiWindow::OnMouseClick(GuiEvent& Event)
{
	for (UINT i = 0; i < children.size(); i++)
	{
		GuiObject* obj = GetChild(i);
		switch (obj->Type())
		{
		case GUIOBJECT_CHECKBOX:
		{
			GuiCheckBox* cb = (GuiCheckBox*)obj;
			if (cb->OnMouseClick(Event))
			{
				Event.Action = cb->Action();
				Event.Sender = cb;
				return true;
				
			}
		}
		case GUIOBJECT_BUTTON:
		{
			GuiButton* btn = NULL;
			try	{btn = (GuiButton*)obj;}catch (...)	{btn = NULL;}
			if (btn)
			{
				if (btn->OnMouseClick(Event))
				{
					Event.Sender = btn;
					Event.Action = btn->GetAction();
					Event.Event = GuiEvent_Capture;
					return true;
				}
			}
		}
		break;
		case GUIOBJECT_LISTBOX:
		{
			GuiListBox* b = (GuiListBox*)obj;
			if (b->OnMouseClick(Event))
			{
				
				Event.Sender = b;
				return true;
			}
		}
		break;
		case GUIOBJECT_BTNCONTAINER:
		{
			GuiButtonContainer* BtnC = (GuiButtonContainer*)obj;
			if (BtnC)
			{
				if (BtnC->OnMouseClick(Event))
				{
					// data will already be filled in the Event struct
					return true;
				}
			}
		}
		break;
		}
		
	}
	
	return false;
}
bool GuiWindow::OnKeyPress(GuiEvent& Event)
{
	for (UINT i = 0; i < children.size(); i++)
	{
		GuiObject* obj = GetChild(i);
		switch (obj->Type())
		{
			case GUIOBJECT_INPUT:
			{
				GuiInputBox* box = (GuiInputBox*)obj;
				return box->OnKeyPress(Event);
			}
			break;
			default:
				break;
		}
	}
}