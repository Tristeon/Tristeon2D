#pragma once
#include "Actors/Behaviours/Behaviour.h"
#include <Serialization/TypeRegister.h>
#include <Registers/BehaviourRegister.h>

#include "Callbacks/IStart.h"
#include "Callbacks/IUpdate.h"

namespace Demo
{
	class Glider : public Tristeon::Behaviour, public Tristeon::IUpdate
	{
		REGISTER_TYPE_H(Glider);
		REGISTER_BEHAVIOUR_H(Glider);
	public:
		json serialize() override;
		void deserialize(json j) override;
		void update() override;

		bool isGliding() const { return gliding; }
	private:
		bool gliding = false;
		float maximumYVelocity = 0;
	};
}
