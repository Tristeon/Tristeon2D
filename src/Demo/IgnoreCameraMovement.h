#pragma once
#include "Actors/Behaviours/Behaviour.h"
#include <Serialization/TypeRegister.h>
#include <Registers/BehaviourRegister.h>

#include "Callbacks/ILateUpdate.h"
#include "Callbacks/IStart.h"
#include "Math/Vector2.h"

namespace Demo
{
	class IgnoreCameraMovement : public Tristeon::Behaviour, public Tristeon::IStart, public Tristeon::ILateUpdate
	{
		REGISTER_TYPE_H(IgnoreCameraMovement);
		REGISTER_BEHAVIOUR_H(IgnoreCameraMovement);
	public:
		json serialize() override;
		void deserialize(json j) override;

		void lateUpdate() override;
		void start() override;
	private:
		Tristeon::Vector2 positionOffset;
	};
}
