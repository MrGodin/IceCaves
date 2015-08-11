
#include "keyboardController.h"

void KBControl::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		bKeys[wParam] = TRUE;
		break;
	case WM_KEYUP:
		bKeys[wParam] = FALSE;
		lastKeyUp = wParam;
		break;;
		default:
			return;
	};
}