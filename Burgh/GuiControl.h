#pragma once

#include "GuiFrame.h"

class GuiControl : public GuiFrame
{
protected:
	static bool mouse_captured;
public:
	
	struct GuiEvent
	{
		UINT Event;
		UINT Action;
		GuiControl* Sender = NULL;
		UINT_PTR Key = 0x0;
		UINT Msg;
		Vec2L Mouse;
		WPARAM wParam;
	};
public:
	GuiControl(GuiFrame::GuiFrameDesc desc)
		:
		GuiFrame(desc)
	{

	}
	virtual ~GuiControl(){}
	// override as needed
	virtual bool OnMouseMove(GuiEvent& Event) { return false; };
	virtual bool OnMouseClick(GuiEvent& Event) { return false; };
	virtual bool OnKeyPress(GuiEvent& Event) { return 0; };
	virtual HRESULT Rasterize(){ DrawFrame(); return S_OK; }
	static void SetMouseCapture(bool captured){ mouse_captured = captured; }
	static bool MouseCaptured(){ return mouse_captured; }

};