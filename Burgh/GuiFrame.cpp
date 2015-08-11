
#include "GuiFrame.h"
IDirect3DDevice9* GuiFrame::pDevice = NULL;

ID3DXSprite* GuiFrame::pSprite = NULL;

HRESULT GuiFrame::DrawFrame()
{
	if (!pDevice)
		return OUT_OF_BOUNDS;

	if (!Visible())
		return NO_DRAW;

	try{
		pDevice->SetTexture(0, frameDesc.pTexture);
		pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, frame, sizeof(tVertex));
		pDevice->SetFVF(D3DFVF_CUSTOMLINEVERTEX);
		pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 8, lines1, sizeof(tLineVertex));
		pDevice->DrawPrimitiveUP(D3DPT_LINELIST, 8, lines2, sizeof(tLineVertex));
	}
	catch (...)
	{
		return OUT_OF_BOUNDS;
	}
	return S_OK;
}
void GuiFrame::Init()
{
	Vec2L Verts[4];
	Verts[0] = { frameDesc.originX, frameDesc.originY };
	Verts[1] = { frameDesc.originX + frameDesc.width, frameDesc.originY };
	Verts[2] = { frameDesc.originX, frameDesc.originY + frameDesc.height };
	Verts[3] = { frameDesc.originX + frameDesc.width, frameDesc.originY + frameDesc.height };
	Vec2F VertsF[4];
	VertsF[0] = Verts[0];
	VertsF[1] = Verts[1];
	VertsF[2] = Verts[2];
	VertsF[3] = Verts[3];

	frame[0] = { VertsF[0].x, VertsF[0].y, 0.0f, 1.0f, frameDesc.baseColor.c0, 0.0f, 0.0f };
	frame[1] = { VertsF[1].x, VertsF[1].y, 0.0f, 1.0f, frameDesc.baseColor.c1, 1.0f, 0.0f };
	frame[2] = { VertsF[2].x, VertsF[2].y, 0.0f, 1.0f, frameDesc.baseColor.c2, 0.0f, 1.0f };
	frame[3] = { VertsF[3].x, VertsF[3].y, 0.0f, 1.0f, frameDesc.baseColor.c3, 1.0f, 1.0f };

	lines1[0] = { VertsF[0].x, VertsF[0].y, 0.0f, 1.0f, frameDesc.outerBorderColor.c0 };
	lines1[1] = { VertsF[1].x, VertsF[1].y, 0.0f, 1.0f, frameDesc.outerBorderColor.c1 };
	lines1[2] = { VertsF[1].x, VertsF[1].y, 0.0f, 1.0f, frameDesc.outerBorderColor.c1 };
	lines1[3] = { VertsF[3].x, VertsF[3].y, 0.0f, 1.0f, frameDesc.outerBorderColor.c3 };

	lines1[4] = { VertsF[3].x, VertsF[3].y, 0.0f, 1.0f, frameDesc.outerBorderColor.c3 };
	lines1[5] = { VertsF[2].x, VertsF[2].y, 0.0f, 1.0f, frameDesc.outerBorderColor.c2 };
	lines1[6] = { VertsF[2].x, VertsF[2].y, 0.0f, 1.0f, frameDesc.outerBorderColor.c2 };
	lines1[7] = { VertsF[0].x, VertsF[0].y, 0.0f, 1.0f, frameDesc.outerBorderColor.c0 };

	lines2[0] = { VertsF[0].x + 1.0f, VertsF[0].y + 1.0f, 0.0f, 1.0f, frameDesc.innerBorderColor.c0 };
	lines2[1] = { VertsF[1].x - 1.0f, VertsF[1].y + 1.0f, 0.0f, 1.0f, frameDesc.innerBorderColor.c1 };
	lines2[2] = { VertsF[1].x - 1.0f, VertsF[1].y + 1.0f, 0.0f, 1.0f, frameDesc.innerBorderColor.c1 };
	lines2[3] = { VertsF[3].x - 1.0f, VertsF[3].y - 1.0f, 0.0f, 1.0f, frameDesc.innerBorderColor.c3 };

	lines2[4] = { VertsF[3].x - 1.0f, VertsF[3].y - 1.0f, 0.0f, 1.0f, frameDesc.innerBorderColor.c3 };
	lines2[5] = { VertsF[2].x + 1.0f, VertsF[2].y - 1.0f, 0.0f, 1.0f, frameDesc.innerBorderColor.c2 };
	lines2[6] = { VertsF[2].x + 1.0f, VertsF[2].y - 1.0f, 0.0f, 1.0f, frameDesc.innerBorderColor.c2 };
	lines2[7] = { VertsF[0].x + 1.0f, VertsF[0].y + 1.0f, 0.0f, 1.0f, frameDesc.innerBorderColor.c0 };

	hotspot.top = frameDesc.originY;
	hotspot.left = frameDesc.originX;
	hotspot.right = hotspot.left + frameDesc.width;
	hotspot.bottom = hotspot.top + frameDesc.height;

}