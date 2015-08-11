
#include "PlayerMove.h"
#include "PlayerStand.h"
#include "PlayerJump.h"
#include "PlayerBounce.h"


void PlayerJump::Update(float dt)
{
	
	if (isThrusting)
	{
		
		pCore->Vel.y += -(pCore->thrust - pCore->anti_gravity);
	}
	else
	{
		pCore->Vel.y += gravity;//  *dt;
		
	}
	if (isMoving)
	{
		pCore->Vel.x += pCore->dir.Translate(pCore->accelX);
			
	}
	else
	{
		pCore->Vel.x *= pCore->decayX;
	}
	// confine to either - or + maxSpeed
	pCore->Vel.y = __min(pCore->maxSpeedY, pCore->Vel.y);
	pCore->Vel.y = __max(-pCore->maxSpeedY, pCore->Vel.y);
	pCore->Vel.x = __min(pCore->maxSpeedX, pCore->Vel.x);
	pCore->Vel.x = __max(-pCore->maxSpeedX, pCore->Vel.x);

	pCore->Pos += pCore->Vel * dt;
}
void PlayerJump::OnCtrlJumpPress()
{
	
	pCore->thrust -= 0.45f;
	if (pCore->thrust < 0.0f)
		pCore->thrust = 0.0f;
}
void PlayerJump::OnCtrlDirRelease()
{
	isMoving = false;
}
void PlayerJump::OnCtrlDirChange(TDirection d)
{
	isMoving = true;
	if (d != pCore->dir)
		pCore->dir = d;
}
void PlayerJump::OnCtrlJumpRelease()
{
	isThrusting = false;
}


void PlayerJump::OnCollision(const RectF rect, const RectF FRect)
{

	if (pCore->Vel.x > 0.0f)
	{

		if (pCore->Vel.y > 0.0f)
		{

			float px = FRect.right - rect.left;
			float py = FRect.bottom - rect.top;
			if (pCore->Vel.y* px > pCore->Vel.x * py)
			{
				// top

				pCore->Pos.y -= py;
				//pCore->Vel.y = 0.0f;
				float initVel = pCore->Vel.y / pCore->mass;
				if (initVel > 2.0f)
					Transition(new PlayerBounce(pCore, false, initVel));
				else
					Transition(new PlayerStand(pCore));
			}
			else
			{
				// side
				pCore->Vel.x = -(pCore->Vel.x * pCore->decayX / 2);
				pCore->Pos.x -= px;

			}
		}
		else //pCore->Vel.y > 0.0f
		{
			float px = FRect.right - rect.left;
			float py = rect.bottom - FRect.top;
			if ((-pCore->Vel.y)* px > pCore->Vel.x * py)
			{
				// top
				pCore->Vel.y = 2.0f;
				pCore->Pos.y += py;
				

			}
			else
			{
				// side
				pCore->Vel.x = -(pCore->Vel.x * pCore->decayX / 2);
				pCore->Pos.x -= px;

			}
		}
	}
	else///pCore->Vel.x > 0.0f
	{

		if (pCore->Vel.y > 0.0f)
		{

			float px = rect.right - FRect.left;
			float py = FRect.bottom - rect.top;
			if (pCore->Vel.y* px > (-pCore->Vel.x) * py)
			{
				// top

				pCore->Pos.y -= py;

				float initVel = pCore->Vel.y / pCore->mass;
				if (initVel > 2.0f)
					Transition(new PlayerBounce(pCore, false, initVel));
				else
					Transition(new PlayerStand(pCore));
			}
			else
			{
				// side
				pCore->Vel.x = -(pCore->Vel.x * pCore->decayX / 2);
				pCore->Pos.x += px;

			}
		}
		else //pCore->Vel.y > 0.0f
		{
			float px = rect.right - FRect.left;
			float py = rect.bottom - FRect.top;
			if ((-pCore->Vel.y)* px > (-pCore->Vel.x) * py)
			{
				// top
				pCore->Vel.y = 0.0f;
				pCore->Pos.y += py;
				pCore->Vel.y = 2.0f;
				
				isThrusting = false;


			}
			else
			{
				// side
				pCore->Vel.x = -(pCore->Vel.x * pCore->decayX / 2);
				pCore->Pos.x += px;

			}
		}
	}
}