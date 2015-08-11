
#include "GuiLoadGame.h"
#include "GuiListBox.h"
#include "GuiContainer.h"
#include "StartMenu.h"

void GuiLoadGame::CreateGuiWindow()
{
	wndDesc.baseColor = QVCWhite;
	wndDesc.height = 256 - 32;
	wndDesc.width = 1024 / 3;
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
	listBoxDesc.frmDesc.width = (64 * 2) + (6 * 2);
	listBoxDesc.frmDesc.height = 5 * 16;
	listBoxDesc.frmDesc.originX = pWindow1->OriginX() + 16;// (core->backBufferWidth / 2) - (listBoxDesc.frmDesc.width / 2);
	listBoxDesc.frmDesc.originY = pWindow1->OriginY() + 48 + 16;// (core->backBufferHeight / 2) - (listBoxDesc.frmDesc.height / 2);
	listBoxDesc.frmDesc.type = GUIOBJECT_LISTBOX;
	listBox1 = new GuiListBox(listBoxDesc);
	listBox1->SetFont(pFonts);
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
				if (lb->Name() == TString("PlayerList"))
				{
					if (lb->SelectedItem())
					{
						int x = 0;
					}
				}
			}
				break;
			case GUIOBJECT_BUTTON:
			{
				
				switch (E.Action)
				{
				case BTN_CANCEL:
					Transition(new GuiStartMenu(core));
					return 0;
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