
#pragma once

#include "GuiCore.h"
#include "GuiWindow.h"
#include "GuiListBox.h"

class GuiState
{
private:
	
protected:
	GuiWindow* pWindow1 = NULL;
	GuiFrame::GuiFrameDesc wndDesc;
	GuiCore* core = NULL;
	UINT action;
	static ID3DXFont* pFonts;
	virtual void CreateChildren() = 0;
	virtual void CreateGuiWindow() = 0;
public:
	GuiState(GuiCore* in_core)
		:
		core(in_core)
	{
		

	};
	virtual ~GuiState()
	{
		SAFE_DELETE(pWindow1);
	}
	//=============================================
	static void SetArrayFonts(ID3DXFont* f){ pFonts = f; }
	UINT Poll(){ return action; }
	void Transition(GuiState* state)
	{
		core->pWindow = state;
		delete this;
	}
	
	virtual GuiListItem* GetSelectedItem(UINT object_type, TString object_name){ return NULL; }
	virtual HRESULT Rasterize() = 0;
	virtual void    ReDraw() = 0;
	virtual void Update() = 0;
	virtual GuiWindow* GetGuiWindow(){ return pWindow1; }
	virtual HRESULT OnCritialError() = 0;
	virtual UINT msgProcState(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){ return 0L; }
};