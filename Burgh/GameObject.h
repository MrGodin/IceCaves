
#pragma once

#include "Utils.h"
#include "StateCores.h"
enum {goTypePlayer = 0x675,goTypeEnemy,goTypeNone};
class GameObject
{
protected:
	UINT type = goTypeNone;
	static IDirect3DDevice9* pDevice;
	static ID3DXSprite* pDrawSprite;
public:
	GameObject()
	{}
	virtual ~GameObject(){}
	
	virtual HRESULT Rasterize(){ return 0; };
	virtual void Update(float dt){};
	virtual RectF GetCRect() = 0;
	virtual Vec2F GetPos() = 0;
	virtual Vec2F GetVel() = 0;
	//============
	UINT Type(){ return type; }
	virtual class ObjectState* GetState() = 0;
	//=============
	static void SetDrawTools(IDirect3DDevice9* dev,ID3DXSprite* sprite)
	{ 
		pDevice = dev;
		pDrawSprite = sprite;
	}
	static ID3DXSprite* GetDrawSprite(){ return pDrawSprite; }
	static IDirect3DDevice9* GetDevice(){ return pDevice; }

	
};