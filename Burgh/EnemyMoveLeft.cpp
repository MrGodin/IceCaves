#include "EnemyMoveLeft.h"


EnemyMoveLeft::EnemyMoveLeft(EnemyCore *core)
	:
	EnemyState(core)
{
}

void EnemyMoveLeft::Update(float dt)
{
	pCore->vel += Vec2F(pCore->thrust, gravity * dt);
	pCore->pos;
}

void EnemyMoveLeft::OnCtrlDirChange(TDirection d)
{
	d.Translate
}

EnemyMoveLeft::~EnemyMoveLeft()
{
}
