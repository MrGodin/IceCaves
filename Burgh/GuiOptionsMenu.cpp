
#include "GuiOptionsMenu.h"
#include "GuiCheckBox.h"
#include "Engine.h"


void GuiOptionsMenu::CreateGuiWindow()
{
	wndDesc.baseColor = QVCWhite;
	wndDesc.height = 256;
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
	GuiFrame::GuiFrameDesc cbDesc;
	cbDesc.baseColor = QVCTransparent;
	cbDesc.height = 18;
	cbDesc.width = 128;
	cbDesc.originX = pWindow1->OriginX() + 16;
	cbDesc.originY = pWindow1->OriginY() + 116;
	cbDesc.type = GUIOBJECT_CHECKBOX;
	GuiCheckBox* cb = new GuiCheckBox(cbDesc, CB_VSYNC);
	cb->SetFont(pFonts);
	cb->Create();
	cb->SetCaption("Hello");
	pWindow1->AddChild(cb);

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
			switch (E.Action)
			{
			case CB_VSYNC:
			{
				
				return E.Action;
				
			}
			
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