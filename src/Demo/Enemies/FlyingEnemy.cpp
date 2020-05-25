#include "FlyingEnemy.h"
#include "Demo/Player/Player.h"
#include "Physics/PhysicsBody.h"

namespace Demo
{
	REGISTER_TYPE_CPP(FlyingEnemy);
	REGISTER_ACTOR_CPP(FlyingEnemy);
	
	void FlyingEnemy::start()
	{
		Enemy::start();
		startPos = position;
	}

	json FlyingEnemy::serialize()
	{
		json j = Enemy::serialize();
		j["typeID"] = TRISTEON_TYPENAME(FlyingEnemy);
		j["patrolSpeed"] = patrolSpeed;
		j["patrolDistance"] = patrolDistance;
		j["chaseSpeed"] = chaseSpeed;
		j["goalDetectDistance"] = goalDetectDistance;
		return j;
	}

	void FlyingEnemy::deserialize(json j)
	{
		Enemy::deserialize(j);
		patrolSpeed = j.value("patrolSpeed", 0);
		patrolDistance = j.value("patrolDistance", 0);
		chaseSpeed = j.value("chaseSpeed", 0);
		goalDetectDistance = j.value("goalDetectDistance", 0);
	}

	void FlyingEnemy::aggro(Tristeon::Player* player)
	{
		Tristeon::Vector2 const goal = startPos + direction * Tristeon::Vector2::up() * patrolDistance;
		pb->setVelocity((Tristeon::Vector2::up() * direction).getNormalized() * patrolSpeed);

		if (Tristeon::Vector2::distance(position, goal) < goalDetectDistance)
			direction *= -1;
	}

	void FlyingEnemy::patrol()
	{
		Tristeon::Vector2 const goal = startPos + direction * Tristeon::Vector2::up() * patrolDistance;
		pb->setVelocity((Tristeon::Vector2::up() * direction).getNormalized() * patrolSpeed);

		if (Tristeon::Vector2::distance(position, goal) < goalDetectDistance)
			direction *= -1;
	}

	void FlyingEnemy::die()
	{
		destroy();
	}
}

#ifdef TRISTEON_EDITOR
namespace DemoEditor
{
	OBJECT_EDITOR_CPP(Demo::FlyingEnemy, FlyingEnemyEditor);
}
#endif