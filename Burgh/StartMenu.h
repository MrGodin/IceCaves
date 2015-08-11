
#pragma once

#include "GuiState.h"

class GuiStartMenu : public GuiState
{
protected:
	virtual void CreateChildren();
	virtual void CreateGuiWindow();
	
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