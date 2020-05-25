#pragma once
#include "Actors/Sprite.h"
#include "Player/Player.h"

namespace Demo
{
	class Projectile : public Tristeon::Sprite, public Tristeon::IStart, public Tristeon::IContactBegin, public Tristeon::ITileContactBegin
	{
		REGISTER_TYPE_H(Projectile);
	public:
		json serialize() override;
		void deserialize(json j) override;
		void start() override;
		void contactBegin(Tristeon::Collider* other) override;
		void tileContactBegin(Tristeon::TileContact const& contact) override;

		void shoot(int direction, float strengthX, float strengthY);

		Tristeon::Player* source = nullptr;
		float damage = 0;

	private:
		Tristeon::PhysicsBody* physicsBody = nullptr;
	};
}
