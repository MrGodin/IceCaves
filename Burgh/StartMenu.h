
#pragma once

#include "GuiState.h"

static TString strMessages[5] = { "Create new game or play a saved game", "Select game options", "Resume pame play", "Get Online Help", "Exit To Windows, Your data will be saved" };

class GuiStartMenu : public GuiState
{
protected:
	virtual void CreateChildren();
	virtual void CreateGuiWindow();
	GuiText* pT = NULL;
public:
	GuiStartMenu(GuiCore* core)
		:
	GuiState(core)
	{
		CreateGuiWindow();
		CreateChildren();
	}
	virtual void    ReDraw()override;
	virtual LRESULT OnCritialError()override;
	virtual HRESULT Rasterize()override;
	virtual UINT msgProcState(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)override;
	virtual void Update()override;
};