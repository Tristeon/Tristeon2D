#pragma once
#include "Actors/Behaviours/Behaviour.h"
#include "Physics/Callbacks/ISensorBegin.h"

#include <Serialization/TypeRegister.h>
#include <Registers/BehaviourRegister.h>

namespace Demo
{
	class NextLevelSign : public Tristeon::Behaviour, public Tristeon::ISensorBegin
	{
		REGISTER_TYPE_H(NextLevelSign);
		REGISTER_BEHAVIOUR_H(NextLevelSign);
		
	public:
		json serialize() override;
		void deserialize(json j) override;
		void sensorBegin(Tristeon::Collider* other) override;

	private:
		Tristeon::String nextScene;
	};
}
