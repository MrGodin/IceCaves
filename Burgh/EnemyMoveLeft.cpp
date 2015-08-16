#include "EnemyMoveLeft.h"
#include "EnemyMoveRight.h"

EnemyMoveLeft::EnemyMoveLeft(EnemyCore *core)
	:
	EnemyState(core)
{
}

void EnemyMoveLeft::Update(float dt)
{
	Vec2F accel(pCore->accel.x * pCore->traction, pCore->accel.y + (gravity * dt));

	pCore->vel.x += (-min(accel.x, pCore->maxSpeed.x));
	pCore->vel.y += min(accel.y, pCore->maxSpeed.y);
	pCore->pos += pCore->vel;
	if (abs(pCore->pos.x + pCore->vel.x) >= abs(pCore->pos.x + pCore->maxSpeed.x))
	{
		OnCtrlDirChange(pCore->dir.Right());
	}
}

void EnemyMoveLeft::OnCtrlDirChange(TDirection d)
{
	pCore->dir = d;
	if (d.IsRight())
	{
		Transition(new EnemyMoveRight(pCore));
	}
}

void EnemyMoveLeft::OnCollision(const RectF &rect, const RectF &FRect)
{
	Vec2F lr(rect.left - FRect.left, FRect.bottom - rect.top);

	if (lr.x < lr.y)
	{
		pCore->vel.x = 0.0f;
		pCore->pos.x = pCore->pos.x - lr.x;
	}
	else if (lr.y < lr.x)
	{
		pCore->vel.y = 0.0f;
		pCore->pos.y = pCore->pos.y - lr.y;
	}

	OnCtrlDirChange(pCore->dir.Right());
}

EnemyMoveLeft::~EnemyMoveLeft()
{
}
