#include "Exit.h"
#include "Window.h"

namespace Demo
{
	REGISTER_TYPE_CPP(Exit);
	REGISTER_ACTOR_CPP(Exit);
	
	json Exit::serialize()
	{
		json j = Button::serialize();
		j["typeID"] = TRISTEON_TYPENAME(Exit);
		return j;
	}

	void Exit::onPress()
	{
#ifdef TRISTEON_EDITOR
		//TODO: Our editor API is lacking in features
#else
		Tristeon::Window::close();
#endif
	}
}

#ifdef TRISTEON_EDITOR
namespace DemoEditor
{
	OBJECT_EDITOR_CPP(Demo::Exit, ExitEditor);
}
#endif