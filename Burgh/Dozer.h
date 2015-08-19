#pragma once
#include "GameObject.h"
#include "2dcamera.h"
#include "SpriteSheet.h"
#include "CollidableObject.h"

class Dozer :
	public GameObject, public CollidableObject
{
public:
	Dozer();
	Dozer(Camera &Cam, int Width, int Height, Vec2F &Position);
	Dozer(Dozer&& D);
	~Dozer();

	Dozer &operator=(Dozer&& D);

	// Inherited from GameObject
	HRESULT Rasterize() override;
	void Update(float dt) override;
	Vec2F GetPos()override;
	Vec2F GetVel()override;
	RectF GetCRect() override;

	D3DXVECTOR3 GetDrawPosition();
	class ObjectState* GetState()override;
	void SetImageindex(UINT index);
	void SetImages(TSpriteSheet* tex);
	void SetPosition(const Vec2F &Pos);
	

	// Inherited from CollidableObject
	RectF  GetAABB()override;
	Vec2F GetVelocity()override;
	Vec2F GetPosition()override;
	void   SetVelocity(Vec2F vel)override;
	float  GetRadius()override;
	Vec2F  GetCenter()override;
	void   Rebound(Vec2F normal)override;


private:
	Camera *pCam = nullptr;
	RectL imageRect;
	TSpriteSheet* pTexture = NULL;
	UINT imageIndex = 0;
	EnemyCore core;
	float maxThrust = 10.0f;
};

