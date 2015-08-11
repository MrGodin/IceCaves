

#pragma once

#include "windows.h"

#define RED(r)(((r)& 0xff) << 16)
#define GREEN(g)(((g)& 0xff) << 8)
#define BLUE(b)((b)& 0xff)
#define ATT(a)(((a)& 0xff) << 24) //transparency

static DWORD Color(long a, long r, long g, long b)
{
	return (ATT(a) | RED(r) | GREEN(g) | BLUE(b));
}

struct QuadVertexColors
{
	DWORD c0 = Color(255, 255, 255, 255);
	DWORD c1 = c0;
	DWORD c2 = c0;
	DWORD c3 = c0;
	QuadVertexColors(){};
	QuadVertexColors(DWORD vc1, DWORD vc2, DWORD vc3, DWORD vc4)
		:
		c0(vc1),
		c1(vc2),
		c2(vc3),
		c3(vc4)
	{

	}
};
//==========================================================
static QuadVertexColors QVCBlue = { Color(255, 0, 0, 225), Color(255, 0, 0, 125), Color(255, 0, 0, 125), Color(255, 0, 0, 225) };
static QuadVertexColors QVCBlueTrans = { Color(155, 0, 0, 225), Color(155, 0, 0, 125), Color(155, 0, 0, 125), Color(155, 0, 0, 225) };

static QuadVertexColors QVCBlueHover = { Color(255, 0, 20, 225), Color(255, 0, 20, 225), Color(255, 0, 20, 225), Color(255, 0, 20, 225) };
static QuadVertexColors QVCRed = { Color(155, 25, 0, 0), Color(155, 225, 0, 0), Color(155, 25, 0, 0), Color(155, 225, 0, 0) };
static QuadVertexColors QVCRedHover = { Color(255, 255, 0, 0), Color(255, 255, 0, 0), Color(255, 255, 0, 0), Color(255, 255, 0, 0) };
static QuadVertexColors QVCWhite = { Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255) };
static QuadVertexColors QVCBlack = { Color(255, 0, 0, 0), Color(255, 0, 0, 0), Color(255, 0, 0, 0), Color(255, 0, 0, 0) };
static QuadVertexColors QVCGreen = { Color(155, 0, 255, 0), Color(255, 0, 255, 0), Color(155, 0, 255, 0), Color(255, 0, 255, 0) };

static QuadVertexColors QVCFrameGrey = { Color(255, 128, 128, 128), Color(155, 128, 128, 128), Color(255, 128, 128, 128), Color(155, 128, 128, 128) };
static QuadVertexColors QVCFrameWhite = { Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255), Color(255, 255, 255, 255) };
static QuadVertexColors QVCDisabled = { Color(155, 128, 128, 128),
Color(155, 128, 128, 128), Color(155, 128, 128, 128), Color(155, 128, 128, 128) };

static QuadVertexColors QVCTransparent = { Color(0, 255, 255, 255), Color(0, 255, 255, 255), Color(0, 255, 255, 255), Color(0, 255, 255, 255) };
static QuadVertexColors QVCBlackTrans1 = { Color(120, 0, 0, 0), Color(120, 0, 0, 0), Color(120, 0, 0, 0), Color(120, 0, 0, 0) };
