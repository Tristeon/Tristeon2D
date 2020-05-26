#pragma once
#include "Actors/Behaviours/Behaviour.h"
#include <Serialization/TypeRegister.h>
#include <Registers/BehaviourRegister.h>


#include "Actors/AnimationSprite.h"
#include "Callbacks/IStart.h"
#include "Callbacks/IUpdate.h"
#include "Physics/Callbacks/IContactBegin.h"

namespace Demo
{
	class PlayerHealth : public Tristeon::Behaviour, public Tristeon::IStart, public Tristeon::IUpdate, public Tristeon::IContactBegin
	{
		REGISTER_TYPE_H(PlayerHealth);
		REGISTER_BEHAVIOUR_H(PlayerHealth);
	public:
		json serialize() override;
		void deserialize(json j) override;

		void start() override;
		void update() override;
		void contactBegin(Tristeon::Collider* other) override;

		void takeHit();
	private:
		unsigned int maxHealth = 0;
		unsigned int currentHealth = 0;

		float fade = -1;

		Tristeon::AnimationSprite* healthBar = nullptr;
	};
}
