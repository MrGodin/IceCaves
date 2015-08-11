
#pragma once

#include "Utils.h"

#define KEY_L 0x4C
class KBControl
{
protected:
	bool bKeys[256];
	UINT_PTR lastKeyUp;
public:
	KBControl()
	{
		for (UINT c = 0; c < 256; c++)
			bKeys[c] = FALSE;
	}
	bool IsKeyLastUp(UINT_PTR key){ return key == lastKeyUp; }
	UINT_PTR LastKeyUp(){ return lastKeyUp; }
	virtual void MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual bool IsKeyDown(UINT_PTR key){ return bKeys[key]; }
	virtual bool IsShiftDown(){ return bKeys[VK_SHIFT]; };

	virtual bool IsCtrlDown(){ return bKeys[VK_CONTROL]; }
};