
#include "PlayerBounce.h"
#include "PlayerMove.h"
#include "PlayerStand.h"
#include "PlayerJump.h"


void PlayerBounce::Update(float dt)
{
	
	pCore->thrust += 0.15f;
	pCore->Vel.y += gravity ;
	if (isMoving)
	{
		pCore->Vel.x += pCore->dir.Translate(pCore->accelX);

	}
	else
	{
		pCore->Vel.x *= pCore->traction;
	}
	// confine to either - or + maxSpeed
	pCore->Vel.y = __min(pCore->maxSpeedY, pCore->Vel.y);
	pCore->Vel.y = __max(-pCore->maxSpeedY, pCore->Vel.y);
	pCore->Vel.x = __min(pCore->maxSpeedX, pCore->Vel.x);
	pCore->Vel.x = __max(-pCore->maxSpeedX, pCore->Vel.x);
	
	pCore->Pos += pCore->Vel * dt;
	if (pCore->Pos.y > InitialBounceY)
	{
		Transition(new PlayerJump(pCore, isMoving, false, pCore->Vel.y));
	}
}
void PlayerBounce::OnCtrlDirRelease()
{
	isMoving = false;
}
void PlayerBounce::OnCtrlDirChange(TDirection d)
{
	isMoving = true;
	if (d != pCore->dir)
		pCore->dir = d;
}
void PlayerBounce::OnCtrlJumpPress()
{
	Transition(new PlayerJump(pCore, isMoving, true, pCore->Vel.y));
}

void PlayerBounce::OnCollision(const RectF &rect, const RectF &FRect)
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
				float resultY = (pCore->Vel.y / pCore->mass);

				pCore->Pos.y -= py;
				if (resultY > 0.0f)
				{
					pCore->Vel.y = -resultY;
					Transition(new PlayerJump(pCore,isMoving,false));
					return;
				}
				else
				{
					pCore->Vel.y = 0.0f;
					Transition(new PlayerStand(pCore));
					return;
				}
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

				float resultY = (pCore->Vel.y / pCore->mass);

				pCore->Pos.y -= py;
				if (resultY > 0.0f)
				{
					pCore->Vel.y = -resultY;
					Transition(new PlayerJump(pCore, isMoving, false));
					return;
				}
				else
				{
					pCore->Vel.y = 0.0f;
					Transition(new PlayerStand(pCore));
					return;
				}
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
				pCore->Vel.y = -pCore->Vel.y;
				pCore->Pos.y += py;
				

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