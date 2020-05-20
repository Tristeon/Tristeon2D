#pragma once
#include "Actors/Actor.h"
#include <Registers/ActorRegister.h>

#include "Actors/AnimationSprite.h"
#include "MovementBehaviour.h"
#include "Physics/CircleCollider.h"
#include "Physics/PhysicsBody.h"

namespace Tristeon
{
	class Player : public AnimationSprite, public IStart
	{
		REGISTER_ACTOR_H(Player)
		REGISTER_TYPE_H(Player)
	public:
		Player() = default;
		virtual ~Player() = default;

		void start() override;
		json serialize() override;
		
		PhysicsBody* physicsBody = nullptr;
		MovementBehaviour* movementBehaviour = nullptr;
		CircleCollider* circleCollider = nullptr;
	};
}

#ifdef TRISTEON_EDITOR
#include <Editor/Dynamic/Objects/Actors/AnimationSpriteEditor.h>

namespace DemoEditor
{
	class PlayerEditor : public TristeonEditor::AnimationSpriteEditor
	{
		OBJECT_EDITOR_H(Tristeon::Player, PlayerEditor);
	};
}
#endif