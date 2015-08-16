
#pragma once

#include "Utils.h"


class ScreenRes
{
private:

public:
	struct DisplayResDesc
	{
		int index = -1;
		DWORD width = 0;
		DWORD height = 0;
	};
public:
	ScreenRes(){}

	void GetCurrentScreenResolution(DisplayResDesc& mode)
	{
		DEVMODE dm;// = { 0 };
		dm.dmSize = sizeof(DEVMODE);
		dm.dmDriverExtra = 0;
		if ((EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm)) != 0)
		{
			mode.index = -1;
			mode.height = dm.dmPelsHeight;
			mode.width = dm.dmPelsWidth;

		}
		else
		{
			mode.index = -1;
			mode.width = mode.height = 0;
		}

	}
};