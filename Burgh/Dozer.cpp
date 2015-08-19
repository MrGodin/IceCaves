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
	ZeroMemory(&core, sizeof(EnemyCore));
	core.pos = Position;
	core.accel.x = 0.05f;
	core.maxSpeed.y = 326.0f;
	core.maxSpeed.x = 5.0f;
	core.dir = TDirection::Left();
	core.traction = 1.0f / 0.988f;
	core.thrust = 12.0f;
	core.anti_gravity = 0.0f;
	core.mass = 2.0f;
	core.size.x = Width;
	core.size.y = Height;
	core.state = new DozerMoveRight(&core);
}

Dozer::Dozer(Dozer&& D)
	:
	pCam(D.pCam),
	imageRect(D.imageRect),
	pTexture(D.pTexture),
	imageIndex(D.imageIndex),
	core(D.core),
	maxThrust(D.maxThrust)
{

}

Dozer &Dozer::operator=(Dozer&& D)
{
	imageRect = D.imageRect;
	imageIndex = 0;	
	core = EnemyCore(D.core);
	maxThrust = D.maxThrust;

	pCam = D.pCam;
	pTexture = D.pTexture;
	//core.state = D.core.state;

	D.pCam = nullptr;
	D.pTexture = nullptr;
	D.core.state = nullptr;

	return (*this);
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
	Vec2F halfSize(core.size / 2.0f);
	RectF bb(-halfSize, halfSize);
	bb.Translate(core.pos.x, core.pos.y);

	return bb;
}

ObjectState* Dozer::GetState()
{
	return core.state;
}

Vec2F Dozer::GetPos()
{
	return GetPosition();
}

Vec2F Dozer::GetVel()
{
	return GetVelocity();
}

void Dozer::SetImageindex(UINT index)
{ 
	imageIndex = index; 
}

void Dozer::SetImages(TSpriteSheet* tex)
{ 
	pTexture = tex; 
}

void Dozer::SetPosition(const Vec2F &Pos)
{
	core.pos.x = Pos.x * 64;
	core.pos.y = Pos.y * 64;
}

Dozer::~Dozer()
{
	SAFE_DELETE(core.state);
}



// Inhertied from CollidableObject
RectF Dozer::GetAABB()
{
	return GetCRect();
}

Vec2F Dozer::GetVelocity()
{
	return core.vel;
}

Vec2F Dozer::GetPosition()
{
	return core.pos;
}

void   Dozer::SetVelocity(Vec2F vel)
{
	core.vel = vel;
}

float  Dozer::GetRadius()
{
	return core.size.Len();
}

Vec2F  Dozer::GetCenter()
{
	return GetPosition();
}

void   Dozer::Rebound(Vec2F normal)
{

}
