#pragma once
#include "Actors/Actor.h"
#include <Registers/ActorRegister.h>

#include "Actors/AnimationSprite.h"
#include "Glider.h"
#include "MovementBehaviour.h"
#include "Physics/CircleCollider.h"
#include "Physics/PhysicsBody.h"
#include "PlayerHealth.h"
#include "Weapon.h"

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
		void update() override;
		json serialize() override;
		void deserialize(json j) override;

		void respawn();
		void freeze();
		void unfreeze();
		
		PhysicsBody* physicsBody = nullptr;
		MovementBehaviour* movementBehaviour = nullptr;
		Demo::Glider* glider = nullptr;
		Demo::Weapon* weapon = nullptr;
		Demo::PlayerHealth* playerHealth = nullptr;
		CircleCollider* circleCollider = nullptr;

	private:
		Vector2 spawnPoint;
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