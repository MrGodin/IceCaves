
#include "PlayerMove.h"
#include "PlayerStand.h"
#include "PlayerJump.h"


void PlayerMove::Update(float dt)
{
	pCore->thrust += 0.15f;
	pCore->Vel.x += pCore->dir.Translate(pCore->accelX);
	// confine to either - or + maxSpeed
	pCore->Vel.x = __min(pCore->maxSpeedX, pCore->Vel.x);
	pCore->Vel.x = __max(-pCore->maxSpeedX, pCore->Vel.x);
	pCore->Pos += pCore->Vel * dt;
}
 void PlayerMove::OnCtrlDirRelease()
 {
	 Transition(new PlayerStand(pCore));
 }
void PlayerMove::OnCtrlDirChange(TDirection d)
{
	
	  pCore->dir = d;
}
void PlayerMove::OnCtrlJumpPress()
{
	Transition(new PlayerJump(pCore, true, true, -0.5f));
}

void PlayerMove::OnUnsupported()
{
	Transition(new PlayerJump(pCore, false, false));
}
void PlayerMove::OnCollision(const RectF rect, const RectF FRect)
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
}