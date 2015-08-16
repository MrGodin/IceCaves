
#pragma once

#include "Utils.h"

class GuiCore
{
public:
	GuiCore(){}
	UINT game_state = gsSplash;
	UINT backBufferWidth = 0;
	UINT backBufferHeight = 0;
	class GuiState* pWindow = NULL;
};