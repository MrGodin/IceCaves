
#pragma once
#include "d3d9.h"
#include "d3dx9.h"
#include <dxerr.h>
#include <string>
#include <sstream>
#include <vector>

#include "windows.h"
#include "time.h"
#include "math.h"
#include <wchar.h>
#include <cstdio>
#include <string>
#include "Vec2.h"
#include "rect.h"
#include "Point.h"
#include "Color.h"
#include "MyString.h"
#include "BiDirection.h"


//#define M_DEBUG

#if defined(DEBUG) | defined(_DEBUG)
#ifndef D3D_DEBUG_INFO
#define D3D_DEBUG_INFO
#endif
#endif

#define HR(x) x;

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if (p) { delete (p);     (p)=NULL; } }
#endif    
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if (p) { delete[] (p);   (p)=NULL; } }
#endif    
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if (p) { (p)->Release(); (p)=NULL; } }
#endif

#ifndef OUT_OF_BOUNDS
#define OUT_OF_BOUNDS -1
#endif

#ifndef NO_DRAW
#define NO_DRAW -2
#endif

#define CB_VSYNC 12345
#define CB_FULLSCRN 12346

#define BTN_CANCEL 333
#define BTN_OK     111
#define BTN_DONE   222

#define LOAD_GAME 86
#define CREATE_NEW_GAME 87
#define KILL_APP  88
#define START_GAME 89
#define RESUME_GAME 90
#define PAUSE_GAME 91
#define LOAD_WINDOW_START 92
#define LOAD_WINDOW_OPTIONS 93
#define LOAD_WINDOW_SPLASH 94
#define LOAD_WINDOW_STORE 95
#define LOAD_WINDOW_SAVE 96
#define LOAD_WINDOW_EXIT 97
#define LOAD_WINDOW_PLAYER 98
#define LOAD_WINDOW_STATS 99
#define LOAD_WINDOW_HELP 100

//=======================================
typedef Vec2F V2;
//=======================================

enum { gsRunning = 0x78ff, gsPaused, gsSplash, gsExit };
enum GUIOBJECT_TYPE{
	GUIOBJECT_WINDOW = 7771, GUIOBJECT_UNDEFINED, GUIOBJECT_BUTTON,
	GUIOBJECT_LABEL, GUIOBJECT_LISTBOX, GUIOBJECT_SLIDER,
	GUIOBJECT_INPUT, GUIOBJECT_KNOB, GUIOBJECT_LISTBOX_ITEM,
	GUIOBJECT_BTNCONTAINER,GUIOBJECT_CHECKBOX
};

enum GUITEXT_ALIGN{ TEXTALIGN_CENTER = 8881, TEXTALIGN_LEFT, TEXTALIGN_RIGHT };


enum EnTileType
{
	ttPassable = 0,
	ttSolid,
	ttPrize,
	ttGamePiece,
	ttSpace,
	ttDiffuse,
	ttIrregular,

	ttNumbTypes,
	ttNone
};
struct STileTypeContainer
{
private:
	EnTileType Types[(int)ttNumbTypes];
protected:
	bool IsType(EnTileType type)
	{
		for (int c = 0; c < (int)ttNumbTypes; c++)
		{
			if (type == Types[c])
				return true;
		}
		return false;
	}
public:
	STileTypeContainer()
	{
		for (int c = 0; c < (int)ttNumbTypes; c++)
			Types[c] = ttNone;
	}
	~STileTypeContainer(){};

	bool Contains(EnTileType type)
	{
		return IsType(type);
	}
	void Add(EnTileType type)
	{
		if (!IsType(type))
		{
			for (int c = 0; c < (int)ttNumbTypes; c++)
			{
				if (Types[c] == ttNone)
				{
					Types[c] = type;
					break;
				}
			}
		}
	};
	void Remove(EnTileType type)
	{

		for (int c = 0; c < (int)ttNumbTypes; c++)
		{
			if (Types[c] == type)
			{
				Types[c] = ttNone;

			}
		}
	}
	void Flush()
	{
		for (int c = 0; c < (int)ttNumbTypes; c++)
			Types[c] = ttNone;
	}
};

