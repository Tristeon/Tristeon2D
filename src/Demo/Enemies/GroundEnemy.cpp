#include "GroundEnemy.h"
#include "Physics/PhysicsBody.h"
#include "Physics/PhysicsWorld.h"
#include "Rendering/GameView.h"

namespace Demo
{
	REGISTER_TYPE_CPP(GroundEnemy);
	REGISTER_ACTOR_CPP(GroundEnemy);
	
	json GroundEnemy::serialize()
	{
		json j = Enemy::serialize();
		j["typeID"] = TRISTEON_TYPENAME(GroundEnemy);
		j["patrolSpeed"] = patrolSpeed;
		j["wallCheckDistance"] = wallCheckDistance;
		j["floorCheckDistance"] = floorCheckDistance;
		j["floorCheckOffset"] = floorCheckOffset;
		return j;
	}

	void GroundEnemy::deserialize(json j)
	{
		Enemy::deserialize(j);
		
		patrolSpeed = j["patrolSpeed"];
		wallCheckDistance = j["wallCheckDistance"];
		floorCheckDistance = j["floorCheckDistance"];
		floorCheckOffset = j["floorCheckOffset"];
	}

	void GroundEnemy::chase(Tristeon::Player* player)
	{
		
	}

	void GroundEnemy::patrol()
	{
		bool wallInFront = Tristeon::PhysicsWorld::raycast(position, { (float)patrolDirection, 0 }, wallCheckDistance);
		bool gapInFront = !Tristeon::PhysicsWorld::raycast(position + Tristeon::Vector2(floorCheckOffset* (float)patrolDirection, 0), Tristeon::Vector2::down(), floorCheckDistance);
		if (wallInFront || gapInFront)
			patrolDirection *= -1;
		
		pb->setVelocity(patrolDirection * patrolSpeed, pb->velocity().y);
	}

	void GroundEnemy::die()
	{
		
	}
}

#ifdef TRISTEON_EDITOR
namespace DemoEditor
{
	OBJECT_EDITOR_CPP(Demo::GroundEnemy, GroundEnemyEditor);
}
#endif