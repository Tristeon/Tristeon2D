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
		Tristeon::Vector2 const velocity = getOwner<Tristeon::Player>()->physicsBody->velocity();
		bool const walking = abs(velocity.x) > 0;
		if (walking)
			getOwner<Tristeon::Player>()->flipX = velocity.x < 0;
		
		auto* player = getOwner<Tristeon::Player>();
		
		if (player->weapon->isCharging())
		{
			if (walking)
				player->setAnimationClip("Project/PlayerShootWalking.clip");
			else
				player->setAnimationClip("Project/PlayerShootIdle.clip");
			return;
		}

		if (player->glider->isGliding())
		{
			player->setAnimationClip("Project/PlayerGlide.clip");
			return;
		}
		
		if (walking)
			getOwner<Tristeon::Player>()->setAnimationClip("Project/PlayerWalk.clip");
		else
			getOwner<Tristeon::Player>()->setAnimationClip("Project/PlayerIdle.clip");
	}
}