
#pragma once

#include "Rect.h"
#include "Vec2.h"
class CollidableObject
{
public:
	virtual RectF  GetAABB() = 0;
	virtual Vec2F  GetVelocity() = 0;
	virtual Vec2F  GetPosition() = 0;
	virtual void   SetVelocity(Vec2F vel) = 0;
	virtual float  GetRadius() = 0;
	virtual Vec2F  GetCenter() = 0;
	virtual void   Rebound(Vec2F normal) = 0;

};