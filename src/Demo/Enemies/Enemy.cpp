#include "Enemy.h"
#include "Physics/PhysicsBody.h"

namespace Demo
{
	void Enemy::start()
	{
		pb = getBehaviour<Tristeon::PhysicsBody>();
	}

	json Enemy::serialize()
	{
		json j = AnimationSprite::serialize();
		j["health"] = health;
		j["attack"] = attack;
		return j;
	}

	void Enemy::deserialize(json j)
	{
		AnimationSprite::deserialize(j);
		health = j["health"];
		attack = j["attack"];
	}

	void Enemy::damage(int const& amount, Tristeon::Player* source)
	{
		health -= amount;
		chasing = source;
		
		if (health <= 0)
			die();
	}

	void Enemy::update()
	{
		AnimationSprite::update();

		if (dead)
			return;

		if (chasing == nullptr)
			patrol();
		else
			chase(chasing);
	}
}