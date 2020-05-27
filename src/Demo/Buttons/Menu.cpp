#include "Menu.h"

namespace Demo
{
	REGISTER_TYPE_CPP(Menu);
	REGISTER_ACTOR_CPP(Menu);

	json Menu::serialize()
	{
		json j = Button::serialize();
		j["typeID"] = TRISTEON_TYPENAME(Menu);
		return j;
	}

	void Menu::onPress()
	{
		Tristeon::SceneManager::load("Menu");
	}
}

#ifdef TRISTEON_EDITOR
namespace DemoEditor
{
	OBJECT_EDITOR_CPP(Demo::Menu, MenuEditor);
}
#endif