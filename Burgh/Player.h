
#pragma once

#include "ObjectState.h"
#include "GameObject.h"
#include "PlayerJump.h"
#include "SpriteSheet.h"
#include "2dcamera.h"
class Player: public GameObject
{
protected:
	PlayerCore core;
	int width, height;
	RectL imageRect;
	TSpriteSheet* pTexture = NULL;
	UINT imageIndex = 0;
	Camera *cam = NULL;
	playerFileData fileData;
	float maxThrust = 22.0f;
public:
	Player(Camera* camera,int w,int h,Vec2F pos)
		:
	GameObject(),
	cam(camera),
	width(w),
	height(h)
	{
		type = goTypePlayer;
		ZeroMemory(&core, sizeof(PlayerCore));
		core.Pos = pos;
		core.Vel.x = 0.0f;
		core.accelX = 2.0f;
		core.maxSpeedX = 226.0f;
		core.maxSpeedY = 326.0f;
		core.dir = TDirection::Right();
		core.traction = 0.988f;
		core.thrust = 12.0f;
		core.anti_gravity = 0.998f;
		core.mass = 2.0f;
		core.decayX = 0.989f;

		core.state = new PlayerJump(&core, false, false);
		
	}
	virtual ~Player()
	{
		SAFE_DELETE(core.state);
	}
	virtual ObjectState* GetState(){ return core.state; }
	virtual Vec2F GetVel(){ return core.Vel; }
	virtual Vec2F GetPos(){ return core.Pos; }
	virtual void Update(float dt)override
	{
		if (core.thrust > maxThrust)
			core.thrust = maxThrust;
		core.state->Update(dt);
	}
	
	virtual RectF GetCRect()override
	{
		RectF r;
		r.bottom = -8.0f;
		r.left = -((float)(width / 2)) - 8.0f;
		r.right = (float)(width / 2) + 8.0f;
		r.top =  -height - 16.0f;
		
		r.Translate(core.Pos.x , core.Pos.y );
		
		return r;
	};
	D3DXVECTOR3 GetDrawPosition()
	{
		
		D3DXVECTOR3 ScreenPosition = D3DXVECTOR3((core.Pos.x - cam->ScreenPos().x) - 32, (core.Pos.y - cam->ScreenPos().y) - 64, 0);
		ScreenPosition += cam->GetPos();
		return ScreenPosition;
	}
	void SetImageindex(UINT index){ imageIndex = index; }
	void SetImages(TSpriteSheet* tex){pTexture = tex;}
	virtual HRESULT Rasterize()override
	{
		return GameObject::GetDrawSprite()->Draw(pTexture->Texture(), &pTexture->GetSector(imageIndex),
			NULL, &GetDrawPosition(), Color(255, 255, 255, 255));
	}

	PlayerCore* GetCore(){ return &core; }
	void SetMaxThrust(float increment){ maxThrust += increment; }
	void SetFileData(const playerFileData d)
	{ 
		fileData = d; 
		// NOTE** // update as needed
		core.traction = fileData.traction;
		core.level = fileData.level;
		core.shield_strength = fileData.shieldstrength;
		core.thrust = fileData.thrust;
		core.tokens = fileData.tokens;
		
	}
	playerFileData GetFileData()
	{
		fileData.traction = core.traction;
		fileData.level = core.level;
		fileData.shieldstrength = core.shield_strength;
		fileData.thrust = core.thrust;
		fileData.tokens = core.tokens;
		fileData.accX = core.accelX;
		fileData.accY = core.accelY;
		fileData.posX = core.Pos.x;
		fileData.posY = core.Pos.y;
		fileData.bounce_absorb = core.bounce_absorb;
		fileData.way_point = core.way_point;
		fileData.anti_gravity = core.anti_gravity;
		fileData.Relics = core.relics;
		
		return fileData;
	}
};