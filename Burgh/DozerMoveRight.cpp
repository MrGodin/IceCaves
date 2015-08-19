#include "DozerMoveRight.h"
#include "DozerMoveLeft.h"

DozerMoveRight::DozerMoveRight(EnemyCore* core)
	:
	EnemyState(core)
{
}

void DozerMoveRight::Update(float dt)
{
	Vec2F accel(pCore->accel.x * pCore->traction, pCore->accel.y + ((gravity * 2.0f) * dt));

	pCore->vel.x += min(accel.x, pCore->maxSpeed.x);
	pCore->vel.y += min(accel.y, pCore->maxSpeed.y);
	pCore->pos += pCore->vel;

	if (abs(pCore->vel.x) >= pCore->maxSpeed.x)
	{
		OnCtrlDirChange(pCore->dir.Left());
	}
}

void DozerMoveRight::OnCtrlDirChange(TDirection d)
{
	pCore->dir = d;
	Transition(new DozerMoveLeft(pCore));
}

void DozerMoveRight::OnCollision(const RectF rect, const RectF FRect)
{
	Vec2F lr(FRect.right - rect.left, FRect.bottom - rect.top);

	if (lr.x < lr.y)
	{
		if ((lr.x > 0.0f) && (pCore->vel.x >= 0.0f))
		{
			pCore->vel.x = 0.0f;
			pCore->pos.x -= lr.x;
			OnCtrlDirChange(pCore->dir.Right());
		}
		else
		{
			pCore->pos += pCore->vel;
		}
	}
	else if (lr.y < lr.x)
	{
		pCore->vel.y = 0.0f;
		pCore->pos.y -= lr.y;
	}	
}

DozerMoveRight::~DozerMoveRight()
{
}

