
#pragma once

#include "Utils.h"
#include "FileStructs.h"
static const float gravity = 4.01f;

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
	int way_point;
	class ObjectState* state = NULL;
	relicData relics;
};

class EnemyCore
{
public:
	EnemyCore(){}
	//BiDirection dir;
	Vec2F pos;
	Vec2F vel;
	Vec2F size;
	Vec2F accel;
	Vec2F maxSpeed;
	TDirection dir;
	float mass;
	float thrust;
	float traction;
	float bounce_absorb;
	float anti_gravity;
	float shield_strength;
	float hit_points;
	float power;
	class ObjectState* state = NULL;

};