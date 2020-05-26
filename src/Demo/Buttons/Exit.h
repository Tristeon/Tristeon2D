#pragma once
#include "Button.h"

namespace Demo
{
	class Exit : public Button
	{
		REGISTER_TYPE_H(Exit);
		REGISTER_ACTOR_H(Exit);

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
	class ExitEditor : public TristeonEditor::SpriteEditor
	{
		OBJECT_EDITOR_H(Demo::Exit, ExitEditor);
	};
}
#endif