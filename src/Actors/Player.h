#pragma once
#include "Actors/Actor.h"
#include <Registers/ActorRegister.h>

#include "Actors/AnimationSprite.h"
#include "Actors/Behaviours/MovementBehaviour.h"
#include "Physics/BoxCollider.h"
#include "Physics/PhysicsBody.h"

namespace Tristeon
{
	class Player : public AnimationSprite, public IStart
	{
		REGISTER_ACTOR_H(Player)
		REGISTER_TYPE_H(Player)
	public:
		Player() = default;
		virtual ~Player() = default;

		void start() override;
		
		PhysicsBody* physicsBody = nullptr;
		MovementBehaviour* movementsBehaviour = nullptr;
		BoxCollider* boxCollider = nullptr;
	};
}
