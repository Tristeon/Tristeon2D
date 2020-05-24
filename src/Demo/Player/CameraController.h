#pragma once
#include "Actors/Behaviours/Behaviour.h"
#include <Registers/BehaviourRegister.h>
#include <Serialization/TypeRegister.h>
#include "Callbacks/ILateUpdate.h"

namespace Demo
{
	class CameraController : public Tristeon::Behaviour, public Tristeon::ILateUpdate
	{
		REGISTER_TYPE_H(CameraController)
		REGISTER_BEHAVIOUR_H(CameraController)

	public:
		json serialize() override;
		void deserialize(json j) override;
		void lateUpdate() override;
	};
}
