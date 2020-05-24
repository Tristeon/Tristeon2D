#include "PlayerAnimations.h"

#include "Math/Math.h"
#include "Player.h"

namespace Demo
{
	REGISTER_TYPE_CPP(PlayerAnimations);
	REGISTER_BEHAVIOUR_CPP(PlayerAnimations)

	json PlayerAnimations::serialize()
	{
		json j;
		j["typeID"] = TRISTEON_TYPENAME(PlayerAnimations);
		return j;
	}

	void PlayerAnimations::deserialize(json j)
	{
		//Empty
	}

	void PlayerAnimations::lateUpdate()
	{
		Tristeon::Vector2 velocity = getOwner<Tristeon::Player>()->physicsBody->velocity();
		if (abs(velocity.x) > 0)
			getOwner<Tristeon::Player>()->setAnimationClip("Project/PlayerWalk.clip");
		else
			getOwner<Tristeon::Player>()->setAnimationClip("Project/PlayerIdle.clip");

		getOwner<Tristeon::Player>()->flipX = velocity.x < 0;
	}
}
