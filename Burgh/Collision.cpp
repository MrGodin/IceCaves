
#include "Collision.h"

void Collision::HandleObjectCollision(GameObject& obj)
{
	for (int c = 0; c < objectCount; c++)
	{
		if (!GP[c])
			continue;

		Object* o = GP[c];
		if (o == &obj)
			continue;

		

		RectF A = o->GetAABB();
		RectF B = obj.GetAABB();
		if (!A.OverLaps(B))
			continue;

		float xd = o->GetCenter().x - obj.GetCenter().x;
		float yd = o->GetCenter().y - obj.GetCenter().y;

		float sumRadius = o->GetRadius() + obj.GetRadius();
		float sqrRadius = sumRadius * sumRadius;

		float distSqr = (xd * xd) + (yd * yd);

		if (distSqr <= sqrRadius)
		{
			Vec2 delta = o->GetCenter() - obj.GetCenter();
			float d = delta.Len();
			// minimum translation distance to push balls apart after intersecting

			Vec2 mtd = delta * (o->GetRadius() + obj.GetRadius() - d) / d;


			// resolve intersection --
			// inverse mass quantities
			float im1 = 1.0f / o->GetMass();
			float im2 = 1.0f / obj.GetMass();


			// impact speed
			Vec2 v = (o->GetVelocity() - obj.GetVelocity());
			float vn = v.x*mtd.Normalize().x + v.y*mtd.Normalize().y;

			// sphere intersecting but moving away from each other already
			if (vn > 0.0f) return NULL;

			//// collision impulse
			float i = (-(1.0f + 1.25f) * vn) / (im1 + im2);
			Vec2 impulse = mtd* i;

			//// change in momentum
			Vec2 velocity = o->GetVelocity() + impulse * im1;
			Vec2 velocity2 = obj.GetVelocity() - impulse*im2;

			velocity.x = max(-120.0f, velocity.x);
			velocity.x = min(120.0f, velocity.x);
			velocity.y = max(-120.0f, velocity.y);
			velocity.y = min(120.0f, velocity.y);

			velocity2.x = max(-120.0f, velocity2.x);
			velocity2.x = min(120.0f, velocity2.x);
			velocity2.y = max(-120.0f, velocity2.y);
			velocity2.y = min(120.0f, velocity2.y);
			o->AngleAccel(vn * 0.001f);


			o->SetVelocity(velocity);
			obj.SetVelocity(velocity2);
			return o;
		}

	}

	return NULL;
}