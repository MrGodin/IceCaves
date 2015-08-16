
#pragma once
#include "ObjectState.h"

class PlayerBounce : public PlayerState
{
protected:
	bool isMoving;
	float InitialBounceY;
public:
	PlayerBounce(PlayerCore* core, bool moving, float initialYVel = 0.0f)
		:
		PlayerState(core),
		isMoving(false)
	
	{
		InitialBounceY = pCore->Pos.y;
		float vY = pCore->Vel.y / pCore->mass;
		(vY > 0.0f) ? pCore->Vel.y = -vY : pCore->Vel.y = 0.0f;
	}
	virtual void Update(float dt)override;
	virtual void OnCtrlDirChange(TDirection d)override;
	virtual void OnCtrlDirRelease()override;
	virtual void OnCtrlJumpPress()override;
	virtual void OnCollision(const RectF &rect, const RectF &FRect)override;
};