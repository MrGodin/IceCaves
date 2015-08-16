
#pragma once

#include "GuiState.h"

class GuiExitMenu : public GuiState
{
protected:
	virtual void CreateChildren();
	virtual void CreateGuiWindow();
	UINT numb_children = 3;
public:
	GuiExitMenu(GuiCore* core)
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