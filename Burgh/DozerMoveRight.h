#pragma once
#include "ObjectState.h"

class DozerMoveRight : public EnemyState
{
public:
	DozerMoveRight(EnemyCore* core);
	~DozerMoveRight();

	// Inherited from ObjectState\EnemyState
	void Update(float dt)override; 
	void OnCtrlDirChange(TDirection d)override;
	void OnCollision(const RectF rect, const RectF FRect)override;

};

