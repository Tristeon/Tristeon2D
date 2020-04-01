#include "PhysicsWorld.h"

#include <Physics/RayCastResult.h>
#include <Rendering/GameView.h>

namespace Tristeon
{
	PhysicsWorld::PhysicsWorld()
	{
		b2Vec2 gravity(0.0f, -10.0f);
		world = std::make_unique<b2World>(gravity);
		world->SetContactListener(&listener);
	}

	void PhysicsWorld::update()
	{
		world->Step(1.0f / 60.0f, velocityIterations, positionIterations);
	}

	float PhysicsWorld::pixelsToMeters(uint32 const& pixels)
	{
		return pixels / 256.0f; //256 pixels is 1 meter
	}

	Vector2 PhysicsWorld::pixelsToMeters(Vector2 const& pixels)
	{
		return pixels / 256.0f;
	}

	uint32 PhysicsWorld::metersToPixels(float const& meters)
	{
		return meters * 256;
	}

	Vector2 PhysicsWorld::metersToPixels(Vector2 const& meters)
	{
		return meters * 256;
	}

	bool PhysicsWorld::raycast(Vector2 const& origin, Vector2 const& direction, float const& distance)
	{
		auto* world = instance()->world.get();

		RaycastResult callback;
		b2Vec2 const point1 = pixelsToMeters(origin).convert<b2Vec2>();
		b2Vec2 const point2 = pixelsToMeters(origin + direction * distance).convert<b2Vec2>();
		world->RayCast(&callback, point1, point2);

		return callback.collider != nullptr;
	}

	bool PhysicsWorld::raycast(Vector2 const& origin, Vector2 const& direction, float const& distance,
		RaycastResult& result)
	{
		auto* world = instance()->world.get();

		b2Vec2 const point1 = pixelsToMeters(origin).convert<b2Vec2>();
		b2Vec2 const point2 = pixelsToMeters(origin + direction * distance).convert<b2Vec2>();
		world->RayCast(&result, point1, point2);

		return result.collider != nullptr;
	}
}