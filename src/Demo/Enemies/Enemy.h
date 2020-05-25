#pragma once
#include "Actors/AnimationSprite.h"

namespace Tristeon {
	class Player;
	class PhysicsBody;
}

namespace Demo
{
	class Enemy : public Tristeon::AnimationSprite, public Tristeon::IStart
	{
	public:
		void start() override;
		
		json serialize() override;
		void deserialize(json j) override;
		
		virtual void damage(int const& amount, Tristeon::Player* source);
		void update() override;
	protected:
		virtual void aggro(Tristeon::Player* player) = 0;
		virtual void patrol() = 0;
		virtual void die() = 0;

		Tristeon::PhysicsBody* pb = nullptr;

		int health = 0;
		int attack = 0;

		Tristeon::Player* chasing = nullptr;
		bool dead = false;
	};
}
