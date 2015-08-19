
#include "GuiLoadGame.h"
#include "GuiListBox.h"
#include "GuiContainer.h"
#include "GuiInput.h"
#include "StartMenu.h"
#include "Engine.h"

void GuiLoadGame::CreateGuiWindow()
{
	wndDesc.baseColor = QVCWhite;
	wndDesc.height = 256 - 32;
	wndDesc.width = (long)(1024.0f / 2);
	wndDesc.hoverColor = QVCWhite;
	wndDesc.innerBorderColor = wndDesc.outerBorderColor = QVCFrameGrey;
	wndDesc.originX = (core->backBufferWidth / 2) - (wndDesc.width / 2);
	wndDesc.originY = (core->backBufferHeight / 2) - (wndDesc.height / 2);
	wndDesc.type = GUIOBJECT_WINDOW;
	wndDesc.pTexture = NULL;

	pWindow1 = new GuiWindow(wndDesc, numbChildren);
	pWindow1->SetFont(pFonts);
	if(FAILED(pWindow1->CreateTexture(L"media\\splash_pause.png")))
		pWindow1->SetTexture(NULL);



}
void GuiLoadGame::CreateChildren()
{
	GuiFrame::GuiFrameDesc desc;// = pWindow1->GetFrameDesc();
	desc.originX = pWindow1->GetFrameDesc().originX + 12;
	desc.originY = pWindow1->GetFrameDesc().originY + 20;
	GuiText* pText = NULL;
	pText = new GuiText(desc, "Load saved game or create new game", TEXTALIGN_LEFT);
	pText->SetColor(Color(255, 0, 255, 200));
	pText->SetFont(pFonts);
	pText->AlignText();
	pWindow1->AddChild(pText);
	desc.originY = pWindow1->GetFrameDesc().originY + 48;

	pText = new GuiText(desc, "Saved Games ", TEXTALIGN_LEFT);
	pText->SetColor(Color(255, 0, 255, 255));
	pText->SetFont(pFonts);
	pText->AlignText();
	pWindow1->AddChild(pText);
	// list Box

	GuiListBox::GuiListBoxDesc listBoxDesc;
	GuiListBox* listBox1 = NULL;
	listBoxDesc.name = "PlayerList";
	listBoxDesc.itemHeight = 16;
	listBoxDesc.maxItemsInList = 25;
	listBoxDesc.numbItemsToDisplay = 5;
	listBoxDesc.frmDesc.baseColor = listBoxDesc.frmDesc.hoverColor = QVCRedHover;// QVCRedHover;
	listBoxDesc.frmDesc.innerBorderColor = QVCFrameGrey;
	listBoxDesc.frmDesc.outerBorderColor = QVCWhite;
	listBoxDesc.frmDesc.width = (64 * 3) + (6 * 2);
	listBoxDesc.frmDesc.height = 5 * 16;
	listBoxDesc.frmDesc.originX = pWindow1->OriginX() + 16;// (core->backBufferWidth / 2) - (listBoxDesc.frmDesc.width / 2);
	listBoxDesc.frmDesc.originY = pWindow1->OriginY() + 48 + 16;// (core->backBufferHeight / 2) - (listBoxDesc.frmDesc.height / 2);
	listBoxDesc.frmDesc.type = GUIOBJECT_LISTBOX;
	listBox1 = new GuiListBox(listBoxDesc);
	listBox1->SetFont(pFonts);
	listBox1->Create();
	TGame::gd3dApp->LoadPlayerListBox(listBox1);
	
	pWindow1->AddChild(listBox1);

	
	
	//~list box
	///////////////////////////////////////////////////////////
	// button container
	///////////////////////////////////////////////////////////
	GuiButtonContainer::GuiContainerDesc contDesc;
	contDesc.align = GuiAlign_Horizontal;
	contDesc.numbObjects = 4;
	contDesc.objHeight = 22;
	contDesc.objWidth = 64;
	contDesc.indent = 6;
	contDesc.frameDesc.baseColor = QVCTransparent;
	contDesc.frameDesc.innerBorderColor = QVCFrameGrey;
	contDesc.frameDesc.outerBorderColor = QVCRedHover;
	contDesc.frameDesc.type = GUIOBJECT_BTNCONTAINER;

	contDesc.width = pWindow1->Width() - 64;
	contDesc.height = 32;
	contDesc.frameDesc.originX = pWindow1->OriginX() + 16;
	contDesc.frameDesc.originY = (pWindow1->OriginY() +  pWindow1->Height()) - (contDesc.height + 32);
	GuiButtonContainer* btnContainer = new GuiButtonContainer(contDesc);
	btnContainer->SetFont(pFonts);
    btnContainer->SetOwner(pWindow1);
	btnContainer->Create();
	 // buttons
	GuiButton::GuiButtonDesc btnDesc;
	btnDesc.frameDesc.baseColor = QVCRed;
	btnDesc.frameDesc.hoverColor = QVCRedHover;
	btnDesc.frameDesc.innerBorderColor = QVCFrameGrey;
	btnDesc.frameDesc.outerBorderColor = QVCWhite;
	btnDesc.txtAlign = TEXTALIGN_CENTER;
	btnDesc.frameDesc.type = GUIOBJECT_BUTTON;
	btnDesc.clientAlign = GuiClientAlignLeft;
	
	btnDesc.Action = CREATE_NEW_GAME;
	btnDesc.Text = L"New";
	btnContainer->Add(btnDesc);

	btnDesc.Action = LOAD_GAME;
	btnDesc.Text = L"Select";
	btnContainer->Add(btnDesc);
	// create a space
	btnDesc.frameDesc.baseColor = btnDesc.frameDesc.hoverColor = 
	btnDesc.frameDesc.innerBorderColor = btnDesc.frameDesc.outerBorderColor = QVCTransparent;
	btnDesc.Action = 0;
	btnDesc.Text = L"";
	btnContainer->Add(btnDesc);
	GuiButton* btn = (GuiButton*)pWindow1->GetLastChild();
	btn->Enabled(false);
	//

	btnDesc.clientAlign = GuiClientAlignRight;
	btnDesc.frameDesc.baseColor = QVCRed;
	btnDesc.frameDesc.hoverColor = QVCRedHover;
	btnDesc.frameDesc.innerBorderColor = QVCFrameGrey;
	btnDesc.frameDesc.outerBorderColor = QVCWhite;
	btnDesc.Action = BTN_CANCEL;
	btnDesc.Text = L"Cancel";
	btnContainer->Add(btnDesc);

	pWindow1->AddChild(btnContainer);


	GuiDisplayPanel::GuiDisplayPanelDesc dsDesc;
	
	dsDesc.cols = 2;
	dsDesc.rows = 5;
	dsDesc.itemHeight = 17;
	dsDesc.maxDisplayItems = 4 * 5;
	dsDesc.frmDesc = listBoxDesc.frmDesc;
	dsDesc.frmDesc.type = GUIOBJECT_DISPLAYPANEL;
	dsDesc.frmDesc.height = listBox1->Height();
	
	dsDesc.frmDesc.baseColor = dsDesc.frmDesc.innerBorderColor = QVCTransparent;
	dsDesc.frmDesc.outerBorderColor = QVCRedHover;
	dsDesc.frmDesc.originX = listBoxDesc.frmDesc.originX + listBoxDesc.frmDesc.width + 22;
	dsDesc.frmDesc.width = (pWindow1->OriginX() + pWindow1->Width()) - (dsDesc.frmDesc.originX + 18);
	GuiDisplayPanel* panel = new GuiDisplayPanel(dsDesc);
	panel->SetFont(pFonts);
	panel->Create();
	pWindow1->AddChild(panel);



}
void GuiLoadGame::ReDraw()
{
	if (pWindow1)
	{
		SAFE_DELETE(pWindow1);
		CreateGuiWindow();
		CreateChildren();
	}
}
LRESULT GuiLoadGame::OnCritialError()
{
	return 0;
};
//=============================================================
HRESULT GuiLoadGame::Rasterize()
{
	 pWindow1->Rasterize();
	 
	 return S_OK;
};
UINT GuiLoadGame::msgProcState(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			break;
		default:
			break;
		}
	}
	break;// end key down
	case WM_LBUTTONDOWN:
	{
		POINT mouse;
		GuiControl::GuiEvent E;
		GetCursorPos(&mouse);
		ScreenToClient(hWnd, &mouse);
		E.Msg = WM_LBUTTONDOWN;
		E.Mouse.x = mouse.x;
		E.Mouse.y = mouse.y;
		if (pWindow1->OnMouseClick(E))
		{
			switch (E.Sender->Type())
			{
			case GUIOBJECT_LISTBOX:
			{
				GuiListBox* lb = (GuiListBox*)E.Sender;
				GuiListItem* selectedItem = lb->SelectedItem();
				if (selectedItem)
				{
					GuiDisplayPanel* panel = (GuiDisplayPanel*)pWindow1->GetChildType(GUIOBJECT_DISPLAYPANEL);
					TGame::gd3dApp->FillPlayerListBoxDisplayPanel(selectedItem->GetText(), panel);

				}

			}
			break;
			case GUIOBJECT_BUTTON:
			{
				
				switch (E.Action)
				{
				case CREATE_NEW_GAME:
				{
					Transition(new GuiInput(core));
					return 0;
				}
				case BTN_CANCEL:
					Transition(new GuiStartMenu(core));
					return 0;
				case LOAD_GAME:
				{
					GuiListBox* lb = (GuiListBox*)pWindow1->GetChildType(GUIOBJECT_LISTBOX);
					if (lb)
					{
						TString str = lb->SelectedItem()->GetText();
						TGame::gd3dApp->LoadPlayer(str);
						return 0;
					}
				}
				}
			}
			break;
			default:
				break;
			}
		}
			return E.Action;
	}
	break;
	case WM_MOUSEMOVE:
	{
		POINT mouse;
		GuiControl::GuiEvent E;
		GetCursorPos(&mouse);
		ScreenToClient(hWnd, &mouse);
		E.Mouse.x = mouse.x;
		E.Mouse.y = mouse.y;
		pWindow1->OnMouseMove(E);
	}
	break;
	case WM_LBUTTONUP:
	{
		GuiControl::SetMouseCapture(false);
	}
		break;
	default:
		return 1;
	}
	return 1;
}
void GuiLoadGame::Update()
{
	GuiButtonContainer* BC = (GuiButtonContainer*)pWindow1->GetChildType(GUIOBJECT_BTNCONTAINER);
	if (BC)
	{
		GuiButton* btn = (GuiButton*)BC->GetChild(1);
		if (GetSelectedItem(GUIOBJECT_LISTBOX, "PlayerList"))
		{
			if (!btn->Enabled())
			   btn->SetEnabled(true);
		}
		else
		{
			btn->SetEnabled(false);
		}
	}
}
GuiListItem*  GuiLoadGame::GetSelectedItem(UINT object_type,TString object_name)
{
	switch (object_type)
	{
		case GUIOBJECT_LISTBOX:
		{
			GuiListBox* lb = (GuiListBox*)pWindow1->GetChildType(object_type);
			if (lb)
			{
				if (lb->Name() == object_name)
				   return lb->SelectedItem();

			}
		}
		default:
			break;
	}
}