#include "Player.h"

#include "PlayerHealth.h"

namespace Tristeon
{
	REGISTER_ACTOR_CPP(Player)
	REGISTER_TYPE_CPP(Player)

	void Player::start()
	{
		glider = getBehaviour<Demo::Glider>();
		weapon = getBehaviour<Demo::Weapon>();
		physicsBody = getBehaviour<PhysicsBody>();
		movementBehaviour = getBehaviour<MovementBehaviour>();
		circleCollider = getBehaviour<CircleCollider>();
		playerHealth = getBehaviour<Demo::PlayerHealth>();
		
		spawnPoint = position;
	}

	void Player::update()
	{
		AnimationSprite::update();

		if (position.y < -64)
			playerHealth->takeHit();
	}

	json Player::serialize()
	{
		json j = AnimationSprite::serialize();
		j["typeID"] = TRISTEON_TYPENAME(Player);
		return j;
	}

	void Player::deserialize(json j)
	{
		AnimationSprite::deserialize(j);
	}

	void Player::respawn()
	{
		physicsBody->setPosition(spawnPoint);
		position = spawnPoint;
	}

	void Player::freeze()
	{
		//physicsBody->setEnabled(false);
		setPaused(true);
	}

	void Player::unfreeze()
	{
		//physicsBody->setEnabled(true);
		setPaused(false);
	}
}

#ifdef TRISTEON_EDITOR
namespace DemoEditor
{
	OBJECT_EDITOR_CPP(Tristeon::Player, PlayerEditor);
}
#endif