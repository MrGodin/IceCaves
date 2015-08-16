
#pragma once
#include "ObjectState.h"

class PlayerMove : public PlayerState
{
public:
	PlayerMove(PlayerCore* core)
		:
		PlayerState(core)
	{

	}
	virtual void Update(float dt)override;
	virtual void OnCtrlDirChange(TDirection d)override;
	virtual void OnCtrlDirRelease()override;
	virtual void OnCtrlJumpPress()override;
	virtual void OnUnsupported()override;
	virtual void OnCollision(const RectF &rect, const RectF &FRect)override;
};