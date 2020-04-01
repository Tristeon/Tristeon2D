#include "RaycastResult.h"

#include <Physics/PhysicsBody.h>
#include <Physics/PhysicsWorld.h>

namespace Tristeon
{
	float RaycastResult::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float fraction)
	{
		auto* body = static_cast<PhysicsBody*>(fixture->GetBody()->GetUserData());

		for (auto& pair : body->fixtures)
		{
			if (pair.second == fixture)
			{
				this->collider = pair.first;
				break;
			}
		}

		this->point = PhysicsWorld::metersToPixels(Vector2::convert(point));
		this->normal = Vector2::convert(normal);
		
		return fraction;
	}
}