#include "Player.h"

namespace Tristeon
{
	REGISTER_ACTOR_CPP(Player)
	REGISTER_TYPE_CPP(Player)

	void Player::start()
	{
		physicsBody = getBehaviour<PhysicsBody>();
		movementBehaviour = getBehaviour<MovementBehaviour>();
		circleCollider = getBehaviour<CircleCollider>();
	}

	json Player::serialize()
	{
		json j = AnimationSprite::serialize();
		j["typeID"] = TRISTEON_TYPENAME(Player);
		return j;
	}
}

#ifdef TRISTEON_EDITOR
namespace DemoEditor
{
	OBJECT_EDITOR_CPP(Tristeon::Player, PlayerEditor);
}
#endif