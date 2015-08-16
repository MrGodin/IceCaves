#pragma once

#include "Utils.h"
#include "Grid.h"



class TSpriteSheet
{
private:
	GridI* pGrid = NULL;
	TString strFileName;
	int iWidth = 0;
	int iHeight = 0;
	int iClipSize = 0;
	IDirect3DTexture9* pTexture = NULL;


	D3DSURFACE_DESC  surface_desc;

protected:
	void Destroy()
	{
		SAFE_RELEASE(pTexture);

		SAFE_DELETE(pGrid);

	}

public:
	TSpriteSheet(TString inFileName, int inClipSize)
		:
		strFileName(inFileName),
		iClipSize(inClipSize),
		pTexture(NULL),
		pGrid(NULL),
		iWidth(0),
		iHeight(0)
	{

	};
	~TSpriteSheet()
	{
		Destroy();
	}
	IDirect3DTexture9* Texture(){ return pTexture; }

	HRESULT Create(IDirect3DDevice9* inDevice)
	{


		if (FAILED(D3DXCreateTextureFromFile(inDevice, strFileName.w_char(), &pTexture)))
		{
			return -1;
		}

		pTexture->GetLevelDesc(0, &surface_desc);
		iWidth = surface_desc.Width;
		iHeight = surface_desc.Height;
		pGrid = new GridI(iWidth, iHeight, iClipSize);


		return S_OK;
	}





	RECT  GetSector(int index)
	{
		RECT r;
		r.top = r.left = r.bottom = r.right = 0;
		if (pGrid)
		{// grid is defined ?

			if (index >= 0)
				r = pGrid->GetRect(index);

		}

		// if grid is not defined
		return r;
	}
};