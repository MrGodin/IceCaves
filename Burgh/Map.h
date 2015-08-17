

#pragma once

#include "mapTile.h"
#include "SpriteSheet.h"
#include "Player.h"
#include "2dCamera.h"


#include "levelstrings.h"


class TTileMap
{
private:
	TGameTile** pTiles = NULL;
	//TPrize** pPrizes = NULL;
	int prize_count = 0;
	int iRows;
	int iCols;
	int iMapWidth;
	int iMapHeight;
	int iTileWidth;
	int iTileHeight;
	int iCount;
	long scrnH = 600;
	long scrnW = 800;

	TSpriteSheet* pSprites;
	TString strFileName;
	char* chMapString;
	V2 ExitPosition;
	struct I2D_CLIP
	{
	public:
		int startX = 0;
		int startY = 0;
		int endX = 0;
		int endY = 0;
		I2D_CLIP(){}
		I2D_CLIP(int sX, int sY, int eX, int eY)
		{
			startX = sX; startY = sY; endX = eX; endY = eY;
		}
	};


	/*TGameTile* GetCollisionPrize(Player* player)
	{
		FRect rect;
		FRect cRect = player->GetCRect();
		Vec2F vel = player->GetCore()->Vel;
		if (vel.x > 0.0f)
		{
			if (vel.y < 0.0f)
			{
				for (int iy = TGameTile::GetIndexYBiasTop(cRect.bottom), iyEnd = TGameTile::GetIndexYBiasBottom(cRect.top);
					iy >= iyEnd; iy--)
				{
					for (int ix = TGameTile::GetIndexXBiasRight(cRect.left), ixEnd = TGameTile::GetIndexXBiasLeft(cRect.right);
						ix <= ixEnd; ix++)
					{


						if (GetTile(ix, iy)->Prize())
						{

							return GetTile(ix, iy);
						}
					}
				}
			}
			else
			{
				for (int iy = TGameTile::GetIndexYBiasBottom(cRect.top), iyEnd = TGameTile::GetIndexYBiasTop(cRect.bottom);
					iy <= iyEnd; iy++)
				{
					for (int ix = TGameTile::GetIndexXBiasRight(cRect.left), ixEnd = TGameTile::GetIndexXBiasLeft(cRect.right);
						ix <= ixEnd; ix++)
					{
						if (GetTile(ix, iy)->Prize())
						{

							return GetTile(ix, iy);;
						}
					}
				}
			}
		}
		else
		{
			if (vel.y < 0.0f)
			{
				for (int iy = TGameTile::GetIndexYBiasTop(cRect.bottom), iyEnd = TGameTile::GetIndexYBiasBottom(cRect.top);
					iy >= iyEnd; iy--)
				{
					for (int ix = TGameTile::GetIndexXBiasLeft(cRect.right), ixEnd = TGameTile::GetIndexXBiasRight(cRect.left);
						ix >= ixEnd; ix--)
					{
						if (GetTile(ix, iy)->Prize())
						{

							return GetTile(ix, iy);
						}
					}
				}
			}
			else
			{
				for (int iy = TGameTile::GetIndexYBiasBottom(cRect.top), iyEnd = TGameTile::GetIndexYBiasTop(cRect.bottom);
					iy <= iyEnd; iy++)
				{
					for (int ix = TGameTile::GetIndexXBiasLeft(cRect.right), ixEnd = TGameTile::GetIndexXBiasRight(cRect.left);
						ix >= ixEnd; ix--)
					{
						if (GetTile(ix, iy)->Prize())
						{

							return GetTile(ix, iy);
						}
					}
				}
			}
		}


		return NULL;
	}*/
	I2D_CLIP DrawClip;
	V2 cam_pos;
	void GetDrawClip()
	{

		DrawClip.startX = ((int)cam_pos.x / iTileWidth);// start
		DrawClip.startY = (int)(cam_pos.y - (scrnH / 2)) / iTileWidth;
		DrawClip.endX = (int)((cam_pos.x + scrnW) / iTileWidth) + 1;// end
		DrawClip.endY = (int)((cam_pos.y + (scrnH)) / iTileWidth) + 1;// iRows;
		if (DrawClip.startY < 0)DrawClip.startY = 0;
		if (DrawClip.endY > iRows)DrawClip.endY = iRows;
		if (DrawClip.startX < 0)DrawClip.startX = 0;
		if (DrawClip.endX > iCols)DrawClip.endX = iCols;
	}
public:
	TTileMap(TString textureFilename, char* chMapString, int map_width, int map_height, int tile_width, int tile_height)
		:
		chMapString(chMapString),
		iMapWidth(map_width),
		iMapHeight(map_height),
		iTileWidth(tile_width),
		iTileHeight(tile_height),
		pTiles(NULL),
		strFileName(textureFilename)
	{

		TGameTile::SetWidthHeight(iTileWidth, iTileHeight);
		TGameTile::SetDirection(TDirection::Right());

		pSprites = new TSpriteSheet(textureFilename, tile_width);
		pSprites->Create(GameObject::GetDevice());
		iCols = map_width / tile_width;
		iRows = map_height / tile_height;
		iCount = iRows * iCols;
		pTiles = new TGameTile*[iCount];
		for (int c = 0; c < iCount; c++)
			pTiles[c] = NULL;




	}
	~TTileMap()
	{
		if (pTiles)
		{
			for (int c = 0; c < iCount; c++)
				SAFE_DELETE(pTiles[c]);

			SAFE_DELETE_ARRAY(pTiles);
		}
		SAFE_DELETE(pSprites);
		/*if (pPrizes)
		{
			for (int c = 0; c < prize_count; c++)
				SAFE_DELETE(pPrizes[c]);

			SAFE_DELETE_ARRAY(pPrizes);
		}*/

	}
	RectF GetBoundary(){ return RectF(0.0f, 0.0f, (float)iMapWidth, (float)iMapHeight); }
	TGameTile* GetTile(int ix, int iy)
	{
		int result = iy  * (iMapWidth / iTileWidth) + ix;
		if (result < 0)
			return NULL;
		return pTiles[result];
	}
	TGameTile* GetTile(int i)
	{

		return pTiles[i];
	}
	void Update(Camera& cam, float dt,DWORD vpX,DWORD vpY)
	{
		cam_pos = cam.ScreenPos();
		cam_pos -= Vec2F((float)vpX, (float)vpY);
		GetDrawClip();
	}
	/*
	void GetCollisionRectsList(RectF cRect, FRectCollisionList& list)
	{
		for (int iy = TGameTile::GetIndexYBiasBottom(cRect.top), iyEnd = TGameTile::GetIndexYBiasTop(cRect.bottom);
			iy <= iyEnd; iy++)
		{
			for (int ix = TGameTile::GetIndexXBiasRight(cRect.left), ixEnd = TGameTile::GetIndexXBiasLeft(cRect.right);
				ix <= ixEnd; ix++)
			{
				if (GetTile(ix, iy)->Solid())
					list.push_back(TGameTile::GetRectIndexed(ix, iy));
			}
		}
	}*/
	bool GetCollisionRectSingle(RectF &cRect, RectF& rect, Vec2F& vel)
	{

		if (vel.x > 0.0f)
		{
			if (vel.y < 0.0f)
			{
				for (int iy = TGameTile::GetIndexYBiasTop(cRect.bottom), iyEnd = TGameTile::GetIndexYBiasBottom(cRect.top);
					iy >= iyEnd; iy--)
				{
					for (int ix = TGameTile::GetIndexXBiasRight(cRect.left), ixEnd = TGameTile::GetIndexXBiasLeft(cRect.right);
						ix <= ixEnd; ix++)
					{

						TGameTile* t = GetTile(ix, iy);
						if (t)
						{
							if (t->Solid())
							{
								rect = TGameTile::GetRectIndexed(ix, iy);

								return true;
							}
						}
					}
				}
			}
			else
			{
				for (int iy = TGameTile::GetIndexYBiasBottom(cRect.top), iyEnd = TGameTile::GetIndexYBiasTop(cRect.bottom);
					iy <= iyEnd; iy++)
				{
					for (int ix = TGameTile::GetIndexXBiasRight(cRect.left), ixEnd = TGameTile::GetIndexXBiasLeft(cRect.right);
						ix <= ixEnd; ix++)
					{
						TGameTile* t = GetTile(ix, iy);
						if (t)
						{
							if (t->Solid())
							{
								rect = TGameTile::GetRectIndexed(ix, iy);

								return true;
							}
						}
					}
				}
			}
		}
		else
		{
			if (vel.y < 0.0f)
			{
				for (int iy = TGameTile::GetIndexYBiasTop(cRect.bottom), iyEnd = TGameTile::GetIndexYBiasBottom(cRect.top);
					iy >= iyEnd; iy--)
				{
					for (int ix = TGameTile::GetIndexXBiasLeft(cRect.right), ixEnd = TGameTile::GetIndexXBiasRight(cRect.left);
						ix >= ixEnd; ix--)
					{
						TGameTile* t = GetTile(ix, iy);
						if (t)
						{
							if (t->Solid())
							{
								rect = TGameTile::GetRectIndexed(ix, iy);


								return true;
							}
						}
					}
				}
			}
			else
			{
				for (int iy = TGameTile::GetIndexYBiasBottom(cRect.top), iyEnd = TGameTile::GetIndexYBiasTop(cRect.bottom);
					iy <= iyEnd; iy++)
				{
					for (int ix = TGameTile::GetIndexXBiasLeft(cRect.right), ixEnd = TGameTile::GetIndexXBiasRight(cRect.left);
						ix >= ixEnd; ix--)
					{						
						TGameTile* t = GetTile(ix, iy);
						if (t)
						{
							if (t->Solid())
							{
								rect = TGameTile::GetRectIndexed(ix, iy);

								return true;
							}
						}
					}
				}
			}
		}


		return false;
	}

	void SetScreenWidthHeight(long h, long w){ scrnW = w ; scrnH = h ; }
	void  DoSupport(GameObject* sprite)
	{
		

		RectF cRect = sprite->GetCRect();
		int iy = TGameTile::GetIndexYBiasBottom(cRect.bottom);
		for (int ix = TGameTile::GetIndexXBiasRight(cRect.left), ixEnd = TGameTile::GetIndexXBiasLeft(cRect.right);
			ix <= ixEnd; ix++)
		{
			TGameTile* t = GetTile(ix, iy);
			if (GetTile(ix, iy)->Solid())
			{
				if (t->Diffuse())
				{
					if (t->DiffuseGone(-0.8f))
					{
						t->RemoveType(ttSolid);

						t->AddType(ttSpace);
						t->ImageIndex(63);
					}
				}
				return;
			}
		}
		sprite->GetState()->OnUnsupported();
		
		
	}
	bool  DoCollision(GameObject* sprite)
	{
		RectF rect;
		RectF sprRect = sprite->GetCRect();		
		Player* pl = NULL;
		bool collided = false;
		/*
		if (sprite->Type() == goTypePlayer)
		{
			pl = (Player*)sprite;
			TGameTile* t = GetCollisionPrize(pl);
			if (t)
			{
				RectF rect = t->GetRectIndexed((int)pl->GetCore()->Pos.x / 64, (int)pl->GetCore()->Pos.y / 64);
				if (pl->Center().x > rect.left && pl->Center().x < rect.right &&
					pl->Center().y > rect.top && pl->Center().y < rect.bottom)
				{

					pl->RemoveFromMap(t->Index(), VK_SPACE);
					t->RemoveType(ttPrize);
					t->AddType(ttSpace);
					t->ImageIndex(64);
					TPrize* prize = t->GetPrize();
					if (prize)
					{
						switch (prize->Type())
						{
						case TPrize::PRIZETYPE::ptToken:
							pl->AddToken();
							break;

						case TPrize::PRIZETYPE::ptThrust:
							pl->AddToken();
							break;

						case TPrize::PRIZETYPE::ptTrackion:
							pl->AddToken();
							break;


						}
					}
				}
			}
		}*/
		Vec2F vel = sprite->GetVel();

		bool hasCollided = GetCollisionRectSingle(sprRect, rect, vel);

		if (hasCollided)
		{
			if (sprite->GetState())
			{
				sprite->GetState()->OnCollision(rect, sprRect);
				collided = true;
			}
		}

		//while (GetCollisionRectSingle(sprite->GetCRect(), rect, vel))
		//{
		//
		//
		//	if (sprite->GetState())
		//	{
		//		sprite->GetState()->OnCollision(rect, sprite->GetCRect());
		//
		//	}
		//	
		//	collided = true;
		//
		//	//float dex = TransformPlayerPositionX(sprite->GetCore()->Pos.x);
		//	//sprite->GetCore()->sCRect.Translate(dex, sprite->GetCore()->Pos.y);
		//}
		//
		//collided = true;
		
		return collided;
	}
	HRESULT Create(char* mapStr,long dX,long dY)
	{

		int prize_inc = 0;
		RECT r;
		r.left = dX;
		r.right = iTileWidth;
		r.bottom = iTileHeight;
		r.top = dY;
		for (int c = 0; c < iRows * iCols; c++)
		{
			switch (mapStr[c])//chMapString[c])
			{
			case 'P':
			case '?':
				prize_count++;
				break;
			}
		}
		//pPrizes = new TPrize*[prize_count];
		TGameTile::SetWidthHeight(iTileWidth, iTileHeight);
		for (int y = 0; y < iRows; y++)
		{
			r.left = 0;
			for (int x = 0; x < iCols; x++)
			{
				const int index = y * iCols + x;
				
				EnTileType tType = ttPassable;
				int image_row = 8;
				int index2 = -1;

				pTiles[index] = new TGameTile(r.left, r.top, D3DCOLOR_ARGB(255, 255, 255, 255));
				pTiles[index]->Index(index);
				r.left += iTileWidth;
				r.right = r.left + iTileWidth;


				switch (mapStr[index])//chMapString[index])
				{
				case '1':
				case '2':
				case '3':
				case '4':

				case 'X':
				{
					pTiles[index]->AddType(ttPassable);
					pTiles[index]->AddType(ttPrize);
					pTiles[index]->ImageIndex(19);



					/* using memcpy to copy string: */


					//sprintf_s(p ,"%s", "X");
				}
				break;
				case '?':
				{
					pTiles[index]->AddType(ttPassable);
					pTiles[index]->AddType(ttPrize);
					pTiles[index]->ImageIndex(16 + 4);
					//TPrize::PrizeDesc desc;

					//desc.index = index;
					//desc.type = TPrize::PRIZETYPE::ptThrust;
					//desc.value = 0.25f;
					//pPrizes[prize_inc] = new TPrize(desc);
					//pTiles[index]->SetPrize(pPrizes[prize_inc]);
					prize_inc++;
					break;
				}
				case 'P':
				{
					pTiles[index]->AddType(ttPrize);
					pTiles[index]->ImageIndex(19);
					//TPrize::PrizeDesc desc;

					//desc.index = index;
					//desc.type = TPrize::PRIZETYPE::ptToken;
					//desc.value = 0.0f;
					//pPrizes[prize_inc] = new TPrize(desc);

					//pTiles[index]->SetPrize(pPrizes[prize_inc]);
					prize_inc++;


				}break;
				case 'Q':
					pTiles[index]->AddType(ttSolid);
					pTiles[index]->ImageIndex(7 + image_row);
					break;

				case 'S':
					pTiles[index]->AddType(ttSolid);
					pTiles[index]->AddType(ttDiffuse);
					pTiles[index]->ImageIndex(5 + image_row);
					pTiles[index]->AddType(ttIrregular);
					break;

				case 'C':
					pTiles[index]->AddType(ttSolid);
					pTiles[index]->ImageIndex(0 + image_row);
					break;
				case 'R':
					pTiles[index]->AddType(ttSolid);
					pTiles[index]->ImageIndex(2 + image_row);
					break;
				case 'L':
					pTiles[index]->AddType(ttSolid);
					pTiles[index]->ImageIndex(1 + image_row);
					break;
				case 'Z':
					pTiles[index]->AddType(ttSolid);
					pTiles[index]->ImageIndex(6 + image_row);
					break;
				case 'W':
					pTiles[index]->AddType(ttSolid);
					pTiles[index]->ImageIndex(3 + image_row);
					break;
				case 'B':
					pTiles[index]->AddType(ttSolid);
					pTiles[index]->ImageIndex(4 + image_row);
					break;
				case ' ':
					pTiles[index]->AddType(ttSpace);
					pTiles[index]->ImageIndex(63);
					break;


				}






			}
			r.top += iTileHeight;
			r.bottom = r.top + iTileHeight;
		}

		return 1;
	}

	//RECT GetImageRect(int index){ return pSprites->GetSector(index); }
	//TEXTURE9 GetTexture(){ return pSprites->Texture(); }

	HRESULT Draw()
	{

		for (int y = DrawClip.startY; y < DrawClip.endY; y++)
		{

			for (int x = DrawClip.startX; x < DrawClip.endX; x++)
			{
				const int index = y * iCols + x;
				TGameTile* t = pTiles[index];
				if (t->IsType(ttSpace))
					continue;
				V2 pos = V2(t->X() - cam_pos.x, t->Y() - cam_pos.y);
				GameObject::GetDrawSprite()->Draw(pSprites->Texture(), &pSprites->GetSector(t->ImageIndex()),
					NULL, &D3DXVECTOR3(pos.x, pos.y, 0.0f), t->Color());


			}
		}

		return 1;
	}
	bool DoDraw(int X, int Y, RectI& rect)
	{
		return (X > rect.left - iTileWidth && X < rect.right && Y > rect.top - iTileHeight && Y < rect.bottom);
	}
	TSpriteSheet* SpriteSheet(){ return pSprites; }
	V2 GetExitPosition(){ return ExitPosition; }
};