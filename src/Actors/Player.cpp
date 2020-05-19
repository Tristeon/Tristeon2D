#include "Player.h"

namespace Tristeon
{
	REGISTER_ACTOR_CPP(Player)
	REGISTER_TYPE_CPP(Player)


	void Player::start()
	{
		physicsBody = getBehaviour<PhysicsBody>();
		movementBehaviour = getBehaviour<MovementBehaviour>();
		boxCollider = getBehaviour<BoxCollider>();
	}
}
