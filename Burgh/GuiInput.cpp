
#include "GuiInput.h"
#include "GuiContainer.h"
#include "GuiInputBox.h"
#include "GuiLoadGame.h"

#include "Engine.h"

void GuiInput::CreateGuiWindow()
{
	wndDesc.baseColor = QVCWhite;
	wndDesc.height = 128;
	wndDesc.width = 1024 / 5;
	wndDesc.hoverColor = QVCWhite;
	wndDesc.innerBorderColor = wndDesc.outerBorderColor = QVCFrameGrey;
	wndDesc.originX = (core->backBufferWidth / 2) - (wndDesc.width / 2);
	wndDesc.originY = (core->backBufferHeight / 2) - (wndDesc.height / 2);
	wndDesc.type = GUIOBJECT_WINDOW;
	wndDesc.pTexture = NULL;

	pWindow1 = new GuiWindow(wndDesc, 1);
	pWindow1->SetFont(pFonts);
	if (FAILED(pWindow1->CreateTexture(L"media\\splash_pause.png")))
		pWindow1->SetTexture(NULL);

}
void GuiInput::CreateChildren()
{
	GuiButtonContainer::GuiContainerDesc contDesc;
	contDesc.align = GuiAlign_Horizontal;
	contDesc.numbObjects = 2;
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
	contDesc.frameDesc.originY = (pWindow1->OriginY() + pWindow1->Height()) - (contDesc.height + 16);
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

	btnDesc.Action = BTN_OK;
	btnDesc.Text = L"OK";
	btnContainer->Add(btnDesc);

	btnDesc.clientAlign = GuiClientAlignRight;
	btnDesc.Action = BTN_CANCEL;
	btnDesc.Text = L"Cancel";
	btnContainer->Add(btnDesc);
	pWindow1->AddChild(btnContainer);

	GuiFrame::GuiFrameDesc txtDesc;
	txtDesc.width = pWindow1->Width();
	txtDesc.height = 16;
	txtDesc.originX = pWindow1->OriginX() + 16;
	txtDesc.originY = ((pWindow1->OriginY() + (pWindow1->Height() / 2) - 8)) - (pWindow1->Height() / 4);
	txtDesc.baseColor = txtDesc.hoverColor = txtDesc.innerBorderColor = txtDesc.outerBorderColor = QVCTransparent;
	GuiText* txt = new GuiText(txtDesc, L"Enter Name", TEXTALIGN_LEFT);
	txt->SetFont(pFonts);
	txt->AlignText();
	pWindow1->AddChild(txt);

	GuiFrame::GuiFrameDesc inDesc;
	inDesc.type = GUIOBJECT_INPUT;
	inDesc.baseColor = QVCWhite;
	inDesc.outerBorderColor = QVCRed;
	inDesc.innerBorderColor = QVCTransparent;
	inDesc.height = 18;
	inDesc.width = pWindow1->Width() - 32;
	inDesc.originX = pWindow1->OriginX() + 16;
	inDesc.originY = txtDesc.originY + 22;
	GuiInputBox* box = new GuiInputBox(inDesc);
	box->SetFont(pFonts);
	box->Create();
	pWindow1->AddChild(box);
}
void GuiInput::ReDraw()
{
	if (pWindow1)
	{
		SAFE_DELETE(pWindow1);
		CreateGuiWindow();
		CreateChildren();
	}
}
LRESULT GuiInput::OnCritialError()
{
	return 0;
};
//=============================================================
HRESULT GuiInput::Rasterize()
{
	return pWindow1->Rasterize();
};
UINT GuiInput::msgProcState(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
	{
		/*switch (wParam)
		{
		case VK_ESCAPE:
			break;
		default:
			break;
		}*/

		GuiControl::GuiEvent E;
		E.Key = wParam;
		if (pWindow1->OnKeyPress(E))
		{
			switch (E.Action)
			{
			case BTN_OK:
			{
				GuiInputBox* box = (GuiInputBox*)pWindow1->GetChildType(GUIOBJECT_INPUT);
				TString str = box->GetText();
				TGame::gd3dApp->CreateNewPlayer(str);
				return 0;
			}
				break;
			default:
				break;
			}
		};
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
			case BTN_OK:
			{
				GuiInputBox* box = (GuiInputBox*)pWindow1->GetChildType(GUIOBJECT_INPUT);
				TString str = box->GetText();
				TGame::gd3dApp->CreateNewPlayer(str);
				return 0;
			}
			case BTN_CANCEL:
				Transition(new GuiLoadGame(core));
				return 0;
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