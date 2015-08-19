
#pragma once

#include "GuiControl.h"

class GuiText : public GuiFrame
{
protected:
	long textHeight = 16;
	UINT alignment;
	int strLen;
	TString pText;
	RectL drawPos;
	DWORD txtColor = 0xffffffff;
	RECT GetStringRect()
	{
		RECT r;
		if (FAILED(pFont->DrawText(
			pSprite,
			pText.w_char(),
			wcslen(pText.w_char()),
			&r,
			DT_CALCRECT,
			0
			)))
		{
			r.bottom = r.left = r.top = r.right = 0;
		};
		return r;
	}
public:
	GuiText(GuiFrameDesc desc, TString txt,UINT align,UINT txtHeight = 16)
		:
		GuiFrame(desc),
		pText(txt),
		alignment(align),
		textHeight(txtHeight)
	{
		strLen = wcslen(pText.w_char());
	}
	WCHAR* Text(){ return pText.w_char(); }
	void   SetText(WCHAR* txt){ pText = txt; strLen = wcslen(pText.w_char()); AlignText(); }
	void    SetFont(ID3DXFont* f){ pFont = f; }
	void    SetColor(DWORD c){ txtColor = c; }
	void AlignText()
	{
		int text_indent = textHeight / 4;

		RECT r = GetStringRect();
		long w = r.right - r.left;
		long h = r.bottom - r.top;
		long right = (frameDesc.originX + frameDesc.width);
		long originX = 0;
		long originY = frameDesc.originY + ((frameDesc.height / 2) - (h / 2));;
		switch (alignment)
		{
		case TEXTALIGN_CENTER:
			originX = frameDesc.originX + ((frameDesc.width / 2) - (w / 2));
			break;
		case TEXTALIGN_LEFT:
			originX = frameDesc.originX + text_indent;
			break;
		case TEXTALIGN_RIGHT:
			originX = right - (w + text_indent);
			break;
		}// end switch alignment

		drawPos.left = originX;
		drawPos.top = originY;
	}
	virtual HRESULT Rasterize()override
	{
		return pFont->DrawText(pSprite, pText.w_char(), strLen, &drawPos.ToRECT(), DT_LEFT | DT_NOCLIP, txtColor);
	}
};