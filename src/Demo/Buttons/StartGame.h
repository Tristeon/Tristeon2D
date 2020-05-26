#pragma once
#include "Button.h"

namespace Demo
{
	class StartGame : public Button
	{
		REGISTER_TYPE_H(StartGame);
		REGISTER_ACTOR_H(StartGame);
	public:
		json serialize() override;
	protected:
		void onPress() override;
	};
}

#ifdef TRISTEON_EDITOR
#include <Editor/Dynamic/Objects/Actors/SpriteEditor.h>

namespace DemoEditor
{
	class StartGameEditor : public TristeonEditor::SpriteEditor
	{
		OBJECT_EDITOR_H(Demo::StartGame, StartGameEditor);
	};
}
#endif