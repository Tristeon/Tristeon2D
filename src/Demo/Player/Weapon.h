#pragma once
#include "Actors/Behaviours/Behaviour.h"
#include "Callbacks/IUpdate.h"
#include <Serialization/TypeRegister.h>
#include <Registers/BehaviourRegister.h>

#include "Actors/AnimationSprite.h"

namespace Demo
{
	class Weapon : public Tristeon::Behaviour, public Tristeon::IStart, public Tristeon::IUpdate
	{
		REGISTER_TYPE_H(Weapon);
		REGISTER_BEHAVIOUR_H(Weapon);
		
	public:
		json serialize() override;
		void deserialize(json j) override;

		void start() override;
		void update() override;

		void shoot(float strength);

		bool isCharging() const { return charging; }
	private:
		Tristeon::AnimationSprite* chargeBar = nullptr;
		Tristeon::AnimationSprite* ammoTens = nullptr;
		Tristeon::AnimationSprite* ammoOnes = nullptr;
		
		bool charging = false;
		float time = 0;

		int ammo = 0;
		float chargeDuration = 0;
		float minimumCharge = 0.1f;
		float throwStrength = 0;
		float throwStrengthY = 0;
		float damage = 0;
	};
}
