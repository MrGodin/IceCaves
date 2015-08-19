#pragma once
#include "ObjectState.h"
#include "StateCores.h"
class DozerMoveLeft : public EnemyState
{
public:
	DozerMoveLeft(EnemyCore *core);
	~DozerMoveLeft();

	void Update(float dt)override;
	void OnCtrlDirChange(TDirection d)override;
	void OnCollision(const RectF rect, const RectF FRect)override;

};

