
#pragma once

#include "GuiState.h"

class GuiLoadGame : public GuiState
{
protected:
	virtual void CreateChildren();
	virtual void CreateGuiWindow();
	unsigned int numbChildren = 2;
	
public:
	GuiLoadGame(GuiCore* core)
		:
		GuiState(core)
	{
		CreateGuiWindow();
		CreateChildren();
		


	}
	virtual ~GuiLoadGame()
	{
		//SAFE_DELETE(pText);
		//SAFE_DELETE(pText2);
	}
	virtual void Update()override{};
	virtual void    ReDraw()override;
	virtual LRESULT OnCritialError()override;
	virtual HRESULT Rasterize()override;
	virtual UINT msgProcState(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)override;
};