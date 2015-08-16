#pragma once
#include "ObjectState.h"
#include "StateCores.h"
class EnemyMoveLeft : public EnemyState
{
public:
	EnemyMoveLeft(EnemyCore *core);
	~EnemyMoveLeft();

	void Update(float dt)override;
	void OnCtrlDirChange(TDirection d)override;
	void OnCollision(const RectF &rect, const RectF &FRect)override;

};

