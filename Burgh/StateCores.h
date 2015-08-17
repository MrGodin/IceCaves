#pragma once

#include "Utils.h"

static const float gravity = 4.01f;
class ObjectState;

class PlayerCore 
{
public:
	PlayerCore(){}
	TDirection dir;
	Vec2F Pos;
	Vec2F Vel;
	UINT  level;
	UINT  tokens;
	float accelX;
	float accelY;
	float decayX;
	float decayY;
	float maxSpeedX;
	float maxSpeedY;
	float thrust;
	float traction;
	float bounce_absorb;
	float anti_gravity;
	float shield_strength;
	float hit_points;
	float power;
	float mass;
	ObjectState* state = NULL;

};

class EnemyCore
{
public:
	EnemyCore();
	EnemyCore(EnemyCore &&ec);
	EnemyCore &operator=(EnemyCore&& ec);

	Vec2F pos;
	Vec2F vel;
	Vec2F accel;
	Vec2F maxSpeed;
	float mass, decayX;
	float thrust;
	float traction;
	float bounce_absorb;
	float anti_gravity;
	float shield_strength;
	float hit_points;
	float power;
	ObjectState* state;
	TDirection dir;
	int width, height;
};