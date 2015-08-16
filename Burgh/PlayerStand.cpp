
#include "PlayerMove.h"
#include "PlayerStand.h"
#include "PlayerJump.h"


void PlayerStand::Update(float dt)
{
	pCore->thrust += 0.15f;
	pCore->Vel.x *= pCore->traction;
	pCore->Pos += pCore->Vel * dt;
}

void PlayerStand::OnCtrlDirChange(TDirection d)
{
	pCore->dir = d;
	Transition(new PlayerMove(pCore));
}
void PlayerStand::OnCtrlJumpPress()
{
	Transition(new PlayerJump(pCore, false, true, -0.5f));
}

void PlayerStand::OnUnsupported()
{
	Transition(new PlayerJump(pCore, false, false));
}
void PlayerStand::OnCollision(const RectF &rect, const RectF &FRect)
{
	if (pCore->Vel.x > 0.0f)
	{
		pCore->Pos.x -= FRect.right - rect.left;
		pCore->Vel.x = -(pCore->Vel.x * pCore->decayX / 2);
	}
	else
	{
		pCore->Pos.x += rect.right - FRect.left;
		pCore->Vel.x = -(pCore->Vel.x * pCore->decayX / 2);
	}
	//pCore->dir.Reverse();
}