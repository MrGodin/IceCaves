#include "Dozer.h"
#include "DozerMoveLeft.h"
#include "DozerMoveRight.h"

Dozer::Dozer()
{
}

Dozer::Dozer(Camera &cam, int Width, int Height, Vec2F &Position)
	:
	pCam(&cam)
{
	type = goTypeEnemy;
	ZeroMemory(&core, sizeof(PlayerCore));
	core.pos = Position;
	core.accel.x = 0.05f;
	core.maxSpeed.y = 326.0f;
	core.maxSpeed.x = 5.0f;
	core.dir = TDirection::Left();
	core.traction = 1.0f / 0.988f;
	core.thrust = 12.0f;
	core.anti_gravity = 0.0f;
	core.mass = 2.0f;
	core.decayX = 0.989f;
	core.width = Width;
	core.height = Height;
	core.state = new DozerMoveRight(&core);
}

D3DXVECTOR3 Dozer::GetDrawPosition()
{	
	Vec2F camOffset(core.pos - pCam->ScreenPos());
	return (D3DXVECTOR3(camOffset.x - 32, camOffset.y - 26, 0) + pCam->GetPos());
}

HRESULT Dozer::Rasterize()
{ 
	D3DXVECTOR3 drawPos(GetDrawPosition());
	IDirect3DTexture9 *pTex = pTexture->Texture();
	RECT rectPos = pTexture->GetSector(imageIndex);
	D3DCOLOR color = Color(255, 255, 255, 255);

	return pDrawSprite->Draw(pTex, &rectPos, NULL, &drawPos, color);
}

void Dozer::Update(float dt)
{
	if (core.vel.x > 0.0f)
	{
		SetImageindex(34);
	}
	else
	{
		SetImageindex(33);
	}
	core.state->Update(dt);
}

RectF Dozer::GetCRect()
{
	int halfWidth = core.width / 2;
	int halfHeight = core.height / 2;
	RectF bb;
	bb.left = -halfWidth;
	bb.right = halfWidth;
	bb.top = -halfHeight;
	bb.bottom = halfHeight;
	/*bb.top = -(halfHeight + 24);
	bb.bottom = (-halfHeight) + 24;*/

	bb.Translate(core.pos.x, core.pos.y);

	return bb;
}

UINT Dozer::Type()
{ 
	return type; 
}

ObjectState* Dozer::GetState()
{
	return core.state;
}

Vec2F Dozer::GetVel()
{
	return core.vel;
}

Vec2F Dozer::GetPos()
{
	return core.pos;
}

void Dozer::SetImageindex(UINT index)
{ 
	imageIndex = index; 
}

void Dozer::SetImages(TSpriteSheet* tex)
{ 
	pTexture = tex; 
}

Dozer::~Dozer()
{
}
