
#include "GuiOptionsMenu.h"
#include "GuiCheckBox.h"
#include "StartMenu.h"
#include "Engine.h"


void GuiOptionsMenu::CreateGuiWindow()
{
	wndDesc.baseColor = QVCWhite;
	wndDesc.height = 256 - 64;
	wndDesc.width = 1024 / 3;
	wndDesc.hoverColor = QVCWhite;
	wndDesc.innerBorderColor = wndDesc.outerBorderColor = QVCFrameGrey;
	wndDesc.originX = (core->backBufferWidth / 2) - (wndDesc.width / 2);
	wndDesc.originY = (core->backBufferHeight / 2) - (wndDesc.height / 2);
	wndDesc.type = GUIOBJECT_WINDOW;
	wndDesc.pTexture = NULL;

	pWindow1 = new GuiWindow(wndDesc, 1);
	pWindow1->SetFont(pFonts);
	pWindow1->CreateTexture(L"media\\splash_pause.png");


}
void GuiOptionsMenu::CreateChildren()
{
	TGame::gd3dApp->GetOptions(vSync, fullscreen);
	
	GuiFrame::GuiFrameDesc cbDesc;
	cbDesc.baseColor = cbDesc.innerBorderColor = cbDesc.outerBorderColor = QVCTransparent;
	cbDesc.height = 18;
	cbDesc.width = 128;
	cbDesc.originX = pWindow1->OriginX() + 16;
	cbDesc.originY = pWindow1->OriginY() + 32+18;
	cbDesc.type = GUIOBJECT_CHECKBOX;
	GuiCheckBox* cb = new GuiCheckBox(cbDesc, CB_VSYNC);
	cb->SetFont(pFonts);
	
	cb->Create();
	cb->Checked(vSync);
	
	cb->SetCaption("Enable VSync");
	pWindow1->AddChild(cb);

	cbDesc.originY = pWindow1->OriginY() + 32 + (18 * 3);
	GuiCheckBox* cb2 = new GuiCheckBox(cbDesc, CB_FULLSCRN);
	cb2->SetFont(pFonts);
	
	cb2->Create();
	cb2->Checked(fullscreen);
	cb2->SetCaption("Enable Full Screen");
	pWindow1->AddChild(cb2);

	GuiButtonContainer* BtnCont = NULL;
	GuiButtonContainer::GuiContainerDesc conDesc;
	conDesc.align = GuiAlign_Horizontal;

	conDesc.numbObjects = 5;
	conDesc.objHeight = 22;
	conDesc.objWidth = 64;
	conDesc.indent = 6;
	conDesc.frameDesc.baseColor = QVCTransparent;
	conDesc.frameDesc.hoverColor = QVCTransparent;
	conDesc.frameDesc.innerBorderColor = QVCTransparent;
	conDesc.frameDesc.outerBorderColor = QVCRedHover;
	long h = (22 * 5) + (6 * (5)) + (6);

	conDesc.frameDesc.originX = pWindow1->OriginX() + 16;
	conDesc.frameDesc.originY = pWindow1->OriginY() + pWindow1->Height() - 64;
	conDesc.frameDesc.type = GUIOBJECT_BTNCONTAINER;
	BtnCont = new GuiButtonContainer(conDesc);
	BtnCont->SetFont(pFonts);
	BtnCont->SetOwner(pWindow1);
	BtnCont->Create();
	GuiButton::GuiButtonDesc BtnDesc;


	BtnDesc.frameDesc.baseColor = QVCRed;
	BtnDesc.frameDesc.hoverColor = QVCRedHover;
	BtnDesc.frameDesc.width = 64;
	BtnDesc.frameDesc.height = 22;
	BtnDesc.frameDesc.originX = 100;
	BtnDesc.frameDesc.originY = 100;

	BtnDesc.txtAlign = TEXTALIGN_CENTER;
	BtnDesc.frameDesc.type = GUIOBJECT_BUTTON;


	BtnDesc.Action = BTN_OK;
	BtnDesc.Text = L"Apply";
	BtnDesc.Index = 0;
	BtnCont->Add(BtnDesc);
	GuiButton* btn = (GuiButton*)BtnCont->GetLastChild();
	btn->SetEnabled(false);

	BtnDesc.Action = BTN_DONE;
	BtnDesc.Text = L"Done";
	BtnDesc.Index = 1;
	BtnCont->Add(BtnDesc);
	btn = (GuiButton*)BtnCont->GetLastChild();
	btn->SetEnabled(false);
	
	BtnDesc.Text = L"Cancel";
	BtnDesc.Action = BTN_CANCEL;
	BtnDesc.Index = 2;
	BtnDesc.clientAlign = GuiClientAlignRight;
	BtnCont->Add(BtnDesc);
	pWindow1->AddChild(BtnCont);

	GuiFrame::GuiFrameDesc txtDesc;
	txtDesc.height = 16;
	txtDesc.width = 100;
	txtDesc.originX = pWindow1->OriginX() + 16;
	txtDesc.originY = pWindow1->OriginY() + 10;
	txtDesc.baseColor = txtDesc.innerBorderColor = txtDesc.outerBorderColor = QVCTransparent;
	txtDesc.type = GUIOBJECT_UNDEFINED;

	GuiText* pT = new GuiText(txtDesc, TString("Welcome To Burgh"), TEXTALIGN_LEFT);
	pT->SetFont(pFonts);
	pT->SetText(L"Game Options - Changes in effect after restart");
	pWindow1->AddChild(pT);
}
void GuiOptionsMenu::ReDraw()
{
	if (pWindow1)
	{
		SAFE_DELETE(pWindow1);
		CreateGuiWindow();
		CreateChildren();
	}
}
LRESULT GuiOptionsMenu::OnCritialError()
{
	return 0;
};
//=============================================================
HRESULT GuiOptionsMenu::Rasterize()
{
	return pWindow1->Rasterize();
};
UINT GuiOptionsMenu::msgProcState(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
			case GUIOBJECT_CHECKBOX:
			{
				GuiCheckBox* cb = (GuiCheckBox*)E.Sender;
				GuiButtonContainer* bc = (GuiButtonContainer*)pWindow1->GetChildType(GUIOBJECT_BTNCONTAINER);
				if (bc)
				{
					GuiButton* btn = (GuiButton*)bc->GetChild(0);
					if (btn)
					   btn->SetEnabled(true);
					btn = (GuiButton*)bc->GetChild(1);
					if (btn)
						btn->SetEnabled(false);
				}
				switch (E.Action)
				{
				case CB_VSYNC:
				{
					vSync = cb->Checked();
				}
					break;
				case CB_FULLSCRN:
					fullscreen = cb->Checked();
					break;
				}
				
			}
			break;
			case GUIOBJECT_BUTTON:
			{
				switch (E.Action)
				{
				case BTN_OK:
				{
					TGame::gd3dApp->SetOptions(vSync, fullscreen);
					GuiCheckBox* cb = (GuiCheckBox*)E.Sender;
					GuiButtonContainer* bc = (GuiButtonContainer*)pWindow1->GetChildType(GUIOBJECT_BTNCONTAINER);
					if (bc)
					{
						GuiButton* btn = (GuiButton*)bc->GetChild(0);
						if (btn)
							btn->SetEnabled(false);

						btn = (GuiButton*)bc->GetChild(1);
						if (btn)
							btn->SetEnabled(true);
					}

					return 0;
				}
					break;
				case BTN_DONE:
				case BTN_CANCEL:
					Transition(new GuiStartMenu(core));
				break;
				}
			}
			break;
			default:
				break;
			}
		};
			
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
		break;
	default:
		return 1;
	}
	return 1;
}