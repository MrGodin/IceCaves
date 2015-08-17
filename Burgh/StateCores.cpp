#include "StateCores.h"
#include "ObjectState.h"

EnemyCore::EnemyCore()
{
	ZeroMemory(this, sizeof(EnemyCore));
}

EnemyCore::EnemyCore(EnemyCore &&ec)
	:
	pos(ec.pos),
	vel(ec.vel),
	accel(ec.accel),
	maxSpeed(ec.maxSpeed),
	mass(ec.mass),
	decayX(ec.decayX),
	thrust(ec.thrust),
	traction(ec.traction),
	bounce_absorb(ec.bounce_absorb),
	anti_gravity(ec.anti_gravity),
	shield_strength(ec.shield_strength),
	hit_points(ec.hit_points),
	power(ec.power),
	state((EnemyState *)ec.state),
	dir(ec.dir),
	width(ec.width),
	height(ec.height)
{
	ec.state = nullptr;
}

EnemyCore &EnemyCore::operator=(EnemyCore &&ec)
{
	pos = ec.pos;
	vel = ec.vel;
	accel = ec.accel;
	maxSpeed = ec.maxSpeed;
	mass = ec.mass;
	decayX = ec.decayX;
	thrust = ec.thrust;
	traction = ec.traction;
	bounce_absorb = ec.bounce_absorb;
	anti_gravity = ec.anti_gravity;
	shield_strength = ec.shield_strength;
	hit_points = ec.hit_points;
	power = ec.power;
	state = (EnemyState *)ec.state;
	dir = ec.dir;
	width = ec.width;
	height = ec.height;
	
	//ec.state = nullptr;
	return (*this);
}