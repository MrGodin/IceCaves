
#include "StartMenu.h"
#include "GuiExitMenu.h"
#include "GuiLoadGame.h"
#include "GuiOptionsMenu.h"

void GuiStartMenu::CreateGuiWindow()
{
	wndDesc.baseColor = QVCWhite;
	wndDesc.height =  256;
	wndDesc.width =  1024 / 3;
	wndDesc.hoverColor = QVCWhite;
	wndDesc.innerBorderColor = wndDesc.outerBorderColor = QVCFrameGrey;
	wndDesc.originX =  (core->backBufferWidth / 2) - (wndDesc.width / 2);
	wndDesc.originY =  (core->backBufferHeight / 2) - (wndDesc.height / 2);
	wndDesc.type = GUIOBJECT_WINDOW;
	wndDesc.pTexture = NULL;

	pWindow1 = new GuiWindow(wndDesc, 1);
	pWindow1->SetFont(pFonts);
	if (FAILED(pWindow1->CreateTexture(L"media\\splash_pause.png")))
	{
		pWindow1->SetTexture(NULL);
	};

	
}
 void GuiStartMenu::CreateChildren()
{
	GuiButtonContainer* BtnCont = NULL;
	GuiButtonContainer::GuiContainerDesc conDesc;
	conDesc.align = GuiAlign_Vertical;
	
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
	conDesc.frameDesc.originY = pWindow1->OriginY() + (pWindow1->Height() / 2) - h / 2;
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
	

	BtnDesc.Action = LOAD_GAME;
	BtnDesc.Text = L"Play";
	BtnCont->Add(BtnDesc);
	GuiButton* btn = (GuiButton*)BtnCont->GetLastChild();
	
	

	BtnDesc.Text = L"Options";
	BtnDesc.Action = LOAD_WINDOW_OPTIONS;
	BtnCont->Add(BtnDesc);


	BtnDesc.Action = RESUME_GAME;
	BtnDesc.Text = L"Resume";
	BtnCont->Add(BtnDesc);


	BtnDesc.Action = LOAD_WINDOW_HELP;
	BtnDesc.Text = L"Help";
	BtnCont->Add(BtnDesc);


	BtnDesc.Action =  LOAD_WINDOW_EXIT;
	BtnDesc.Text = L"Quit";
	BtnCont->Add(BtnDesc);
	pWindow1->AddChild(BtnCont);
}
void GuiStartMenu::ReDraw()
{
	if (pWindow1)
	{
		SAFE_DELETE(pWindow1);
		CreateGuiWindow();
		CreateChildren();
	}
}
LRESULT GuiStartMenu::OnCritialError()
{
	return 0;
};
//=============================================================
HRESULT GuiStartMenu::Rasterize()
{
	return pWindow1->Rasterize();
};
void GuiStartMenu::Update()
{
	
}
UINT GuiStartMenu::msgProcState(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
			case KILL_APP:
				return E.Action;
			case LOAD_WINDOW_OPTIONS:
				Transition(new GuiOptionsMenu(core));
				return 0;

			case LOAD_GAME:
			{
				Transition(new GuiLoadGame(core));
			}
				break;
			case RESUME_GAME:
			{
				
			}
				break;
			case LOAD_WINDOW_EXIT:
				Transition(new GuiExitMenu(core));
				return 0;

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
		break;
		default:
			return 1;
	}
	return 1;
}