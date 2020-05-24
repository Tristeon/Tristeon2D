#pragma once
#include "Actors/Sprite.h"
#include "Physics/Callbacks/IContactBegin.h"
#include <Registers/ActorRegister.h>

namespace Demo
{
	class DeathPit : public Tristeon::Sprite, public Tristeon::IContactBegin
	{
		REGISTER_TYPE_H(DeathPit);
		REGISTER_ACTOR_H(DeathPit);

	public:
		void contactBegin(Tristeon::Collider* other) override;
		json serialize() override;
	};
}

#ifdef TRISTEON_EDITOR
#include <Editor/Dynamic/Objects/Actors/SpriteEditor.h>

namespace DemoEditor
{
	class DeathPitEditor : public TristeonEditor::SpriteEditor
	{
		OBJECT_EDITOR_H(Demo::DeathPit, DeathPitEditor);
	};
}
#endif