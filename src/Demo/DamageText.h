#pragma once
#include "Actors/AnimationSprite.h"

namespace Tristeon {
	struct Vector2;
}

namespace Demo
{
	class DamageText : public Tristeon::AnimationSprite
	{
	public:
		static void drawDamage(Tristeon::Vector2 const& position, int const& amount);

		void update() override;
	private:
		float destroyTimer;
	};
}
