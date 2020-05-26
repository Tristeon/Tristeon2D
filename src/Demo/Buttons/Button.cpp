#include "Button.h"

#include "Input/Mouse.h"
#include "Rendering/GameView.h"

namespace Demo
{
	void Button::update()
	{
		if (Tristeon::Mouse::pressed(Tristeon::Mouse::Left) && getAABB().contains(Tristeon::GameView::screenToWorld(Tristeon::Mouse::position())))
			onPress();
	}
}