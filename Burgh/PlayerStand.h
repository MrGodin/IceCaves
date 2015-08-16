
#pragma once
#include "ObjectState.h"

class PlayerStand : public PlayerState
{
public:
	PlayerStand(PlayerCore* core)
		:
		PlayerState(core)
	{
		pCore->Vel.y = 0.0f;
	}
	virtual void Update(float dt)override;
	virtual void OnCtrlDirChange(TDirection d)override;
	virtual void OnCtrlJumpPress()override;
	virtual void OnUnsupported()override;
	virtual void OnCollision(const RectF &rect, const RectF &FRect)override;
};