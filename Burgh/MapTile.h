
#include "Utils.h"


// x + width * y ( index of tile )
class TGameTile
{


public:
	TGameTile(){}
	TGameTile(int x, int y, D3DXCOLOR color);
	virtual ~TGameTile();

	bool      DiffuseGone(float inc)
	{
		LONG T = 255;
		diffuse_rate += inc;
		color = D3DCOLOR_ARGB((LONG)(T + diffuse_rate), 255, 255, 255);
		if (T + diffuse_rate < 25)
		{
			diffuse_rate = 0;

			return true;
		}
		return false;
	}

	void      TextureName(TString s){ strTextureName = s; };
	TString   TextureName(){ return strTextureName; }
	int       X(){ return (int)x; }
	int       Y(){ return (int)y; }
	bool    IsType(EnTileType type){ return enTypes.Contains(type); }
	bool    Passable(){ return enTypes.Contains(ttPassable); }
	bool    Solid(){ return enTypes.Contains(ttSolid); }
	bool    Prize(){ return enTypes.Contains(ttPrize); }
	bool    GamePiece(){ return enTypes.Contains(ttGamePiece); }
	bool    Space(){ return enTypes.Contains(ttSpace); }
	bool    Diffuse(){ return enTypes.Contains(ttDiffuse); }
	void    AddType(EnTileType type){ enTypes.Add(type); }
	void    RemoveType(EnTileType type){ enTypes.Remove(type); }
	void    FlushTypes(){ enTypes.Flush(); }
	void     ImageIndex(int val){ iImageIndex = val; }
	int     ImageIndex(){ return iImageIndex; }
public:
	static void  SetWidthHeight(int w, int h){ width = w; height = h; }
	D3DXCOLOR Color(){ return color; }
	void      Color(D3DXCOLOR val){ color = val; }
	void Index(int val){ iIndex = val; }
	int  Index(){ return iIndex; };
	
	static int   GetIndexXBiasRight(float x)
	{
		return (int)x / width;
	}
	static int   GetIndexXBiasLeft(float x)
	{
		int ix = (int)x / width;
		if ((float)(ix * width) == x)
			ix--;

		return ix;
	}
	static int   GetIndexYBiasBottom(float y)
	{
		return (int)y / height;
	}
	static int   GetIndexYBiasTop(float y)
	{
		int iy = (int)y / height;
		if ((float)(iy * height) == y)
			iy--;

		return iy;
	}
	static RectF GetRectIndexed(int ix, int iy)
	{


		return RectF((float)(iy * height), (float)(ix)* width,
			(float)(ix + 1) * width, (float)(iy + 1) * height);
	}
	static RectF GetRectScreenPos(float ix, float iy)
	{
		return RectF((float)(GetIndexYBiasBottom(iy) * height), (float)(GetIndexXBiasRight(ix)) * width,
			(float)(GetIndexXBiasRight(ix) + 1) * width, (float)(GetIndexYBiasBottom(iy) + 1) * height);
	}
	static void  SetDirection(const TDirection& d){ direction = TDirection(d); };
	static TDirection direction;


private:
	static int width;
	static int height;
	D3DXCOLOR color;

	float x;
	float y;
	float diffuse_rate;
	TString strTextureName;
	int   iImageIndex;
	int   iIndex;
	STileTypeContainer enTypes;
	//TPrize* pPrize = NULL;

};