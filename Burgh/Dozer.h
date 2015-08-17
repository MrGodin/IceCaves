#pragma once
#include "GameObject.h"
#include "2dcamera.h"
#include "SpriteSheet.h"

class Dozer :
	public GameObject
{
public:
	Dozer();
	Dozer(Camera &Cam, int Width, int Height, Vec2F &Position);
	Dozer(Dozer&& D);
	~Dozer();

	Dozer &operator=(Dozer&& D);

	HRESULT Rasterize() override;
	void Update(float dt) override;
	D3DXVECTOR3 GetDrawPosition();
	RectF GetCRect() override;
	class ObjectState* GetState()override;
	Vec2F GetVel()override;
	Vec2F GetPos()override;
	void SetImageindex(UINT index);
	void SetImages(TSpriteSheet* tex);
	void SetPosition(const Vec2F &Pos);
	UINT Type();

private:
	Camera *pCam = nullptr;
	RectL imageRect;
	TSpriteSheet* pTexture = NULL;
	UINT imageIndex = 0;
	EnemyCore core;
	float maxThrust = 10.0f;
};

