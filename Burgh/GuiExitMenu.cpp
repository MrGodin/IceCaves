
#include "GuiExitMenu.h"
#include "GuiButton.h"
#include "StartMenu.h"

void GuiExitMenu::CreateGuiWindow()
{
	wndDesc.baseColor = QVCWhite;
	wndDesc.height = 128;
	wndDesc.width = 522 / 3;
	wndDesc.hoverColor = QVCWhite;
	wndDesc.innerBorderColor = wndDesc.outerBorderColor = QVCFrameGrey;
	wndDesc.originX = (core->backBufferWidth / 2) - (wndDesc.width / 2);
	wndDesc.originY = (core->backBufferHeight / 2) - (wndDesc.height / 2);
	wndDesc.type = GUIOBJECT_WINDOW;
	wndDesc.pTexture = NULL;

	pWindow1 = new GuiWindow(wndDesc, numb_children);
	pWindow1->SetFont(pFonts);
	if (FAILED(pWindow1->CreateTexture(L"media\\splash_pause.png")))
	{
		pWindow1->SetTexture(NULL);
	};


}
void GuiExitMenu::CreateChildren()
{
	GuiButton::GuiButtonDesc BtnDesc;
	GuiButton* pButton = NULL;
	GuiText* txt;
	// Text
	GuiFrame::GuiFrameDesc txtDesc;
	txtDesc.width = pWindow1->Width();
	txtDesc.height = 16;
	txtDesc.originX = pWindow1->OriginX();
	txtDesc.originY = ((pWindow1->OriginY() + (pWindow1->Height() / 2) - 8)) - (pWindow1->Height() / 4);
	txtDesc.baseColor = txtDesc.hoverColor = txtDesc.innerBorderColor = txtDesc.outerBorderColor = QVCTransparent;
	txt = new GuiText(txtDesc, L"Exit to Windows ?", TEXTALIGN_CENTER);
	txt->SetFont(pFonts);
	txt->AlignText();
	pWindow1->AddChild(txt);
	//~
	
	BtnDesc.frameDesc.baseColor = QVCRed;
	BtnDesc.frameDesc.hoverColor = QVCRedHover;
	BtnDesc.frameDesc.width = 64;
	BtnDesc.frameDesc.height = 16;
	BtnDesc.frameDesc.originX = pWindow1->OriginX() + 16;
	BtnDesc.frameDesc.originY = pWindow1->OriginY() + (pWindow1->Height() - (22 +  16));

	BtnDesc.txtAlign = TEXTALIGN_CENTER;
	BtnDesc.frameDesc.type = GUIOBJECT_BUTTON;


	BtnDesc.Action = BTN_OK;
	BtnDesc.Text = L"Exit";
	pButton = new GuiButton(BtnDesc);
	pButton->SetFont(pFonts);
	pWindow1->AddChild(pButton);

	BtnDesc.frameDesc.originX = pWindow1->OriginX() + BtnDesc.frameDesc.width  + 32;

	BtnDesc.Action = BTN_CANCEL;
	BtnDesc.Text = L"Cancel";
	GuiButton* pButton2 = new GuiButton(BtnDesc);
	pButton2->SetFont(pFonts);
	pWindow1->AddChild(pButton2);

}
void GuiExitMenu::ReDraw()
{
	if (pWindow1)
	{
		SAFE_DELETE(pWindow1);
		CreateGuiWindow();
		CreateChildren();
	}
}
LRESULT GuiExitMenu::OnCritialError()
{
	return 0;
};
//=============================================================
HRESULT GuiExitMenu::Rasterize()
{
	return pWindow1->Rasterize();
};
void GuiExitMenu::Update()
{
	
}
UINT GuiExitMenu::msgProcState(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
			switch (E.Action)
			{
			case BTN_CANCEL:
				Transition(new GuiStartMenu(core));
				return 0;
			case BTN_OK:
				return KILL_APP;
			default:
				break;
			}
		}
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