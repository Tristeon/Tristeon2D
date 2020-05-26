#include "Projectile.h"


#include "DamageText.h"
#include "Enemies/Enemy.h"

namespace Demo
{
	json Projectile::serialize()
	{
		json j = Sprite::serialize();
		j["typeID"] = TRISTEON_TYPENAME(Projectile);
		return j;
	}

	void Projectile::deserialize(json j)
	{
		//Empty
	}

	void Projectile::start()
	{
		physicsBody = getBehaviour<Tristeon::PhysicsBody>();
	}

	void Projectile::contactBegin(Tristeon::Collider* other)
	{
		if (other->getOwner<Enemy>())
		{
			DamageText::drawDamage(position, damage);
			
			other->getOwner<Enemy>()->damage(damage, source);
		}

		if (!other->getOwner<Tristeon::Player>())
			destroy();
	}

	void Projectile::tileContactBegin(Tristeon::TileContact const& contact)
	{
		destroy();
	}

	void Projectile::shoot(int direction, float strengthX, float strengthY)
	{
		physicsBody->setVelocity(strengthX * direction, strengthY);
		std::cout << "Projectile shot" << std::endl;
	}
}
