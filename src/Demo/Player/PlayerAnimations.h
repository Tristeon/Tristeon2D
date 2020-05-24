#pragma once
#include "Actors/Behaviours/Behaviour.h"
#include <Serialization/TypeRegister.h>
#include <Registers/BehaviourRegister.h>
#include <Callbacks/ILateUpdate.h>

namespace Demo
{
	class PlayerAnimations : public Tristeon::Behaviour, public Tristeon::ILateUpdate
	{
		REGISTER_TYPE_H(PlayerAnimations);
		REGISTER_BEHAVIOUR_H(PlayerAnimations);

	public:
		json serialize() override;
		void deserialize(json j) override;
		void lateUpdate() override;
	};
}
