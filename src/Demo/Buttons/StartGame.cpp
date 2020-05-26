#include "StartGame.h"

namespace Demo
{
	REGISTER_TYPE_CPP(StartGame);
	REGISTER_ACTOR_CPP(StartGame);

	json StartGame::serialize()
	{
		json j = Button::serialize();
		j["typeID"] = TRISTEON_TYPENAME(StartGame);
		return j;
	}

	void StartGame::onPress()
	{
		Tristeon::SceneManager::load("Scene");
	}
}

#ifdef TRISTEON_EDITOR
namespace DemoEditor
{
	OBJECT_EDITOR_CPP(Demo::StartGame, StartGameEditor);
}
#endif