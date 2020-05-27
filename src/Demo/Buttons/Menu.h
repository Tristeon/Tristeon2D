#pragma once
#include "Button.h"

namespace Demo
{
	class Menu : public Button
	{
		REGISTER_TYPE_H(Menu);
		REGISTER_ACTOR_H(Menu);
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
	class MenuEditor : public TristeonEditor::SpriteEditor
	{
		OBJECT_EDITOR_H(Demo::Menu, MenuEditor);
	};
}
#endif