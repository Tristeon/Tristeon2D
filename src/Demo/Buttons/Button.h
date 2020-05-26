#pragma once
#include "Actors/Sprite.h"
#include "Callbacks/IUpdate.h"

namespace Demo
{
	class Button : public Tristeon::Sprite, public Tristeon::IUpdate
	{
	public:
		void update() override;
	protected:
		virtual void onPress() = 0;
	};
}