
#pragma once
#include "StateCores.h"
class ObjectState
{
protected:
	virtual void Transition(ObjectState* state) = 0;
	
public:
	ObjectState(){}
	
	virtual void Update(float dt) = 0;
	virtual void OnCtrlDirChange(TDirection d){}
	virtual void OnCtrlDirRelease(){}
	virtual void OnCtrlJumpPress(){}
	virtual void OnCtrlJumpRelease(){}
	virtual void OnUnsupported(){}
	virtual void OnCollision(const RectF &rect, const RectF &FRect){}
};

class PlayerState : public ObjectState
{
protected:
	PlayerCore* pCore = NULL;
public:
	PlayerState(PlayerCore* core)
		:
	pCore(core)
	{

	}
	virtual void Transition(ObjectState* state)
	{
		pCore->state = state;
		delete this;
	}
};

class EnemyState : public ObjectState
{
protected:
	EnemyCore* pCore = NULL;
public:
	EnemyState(EnemyCore* core)
		:
		pCore(core)
	{

	}
	EnemyState(EnemyState &&es)
		:
		pCore(es.pCore)
	{
		es.pCore = nullptr;
	}
	EnemyState &operator=(EnemyState &&es)
	{
		pCore = es.pCore;
		es.pCore = nullptr;
	}
	void Transition(ObjectState* state) override
	{
		pCore->state = state;
		delete this;
	}
};