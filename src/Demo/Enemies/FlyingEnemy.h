#pragma once
#include "Enemy.h"
#include <Serialization/TypeRegister.h>
#include <Registers/ActorRegister.h>

namespace Demo
{
	class FlyingEnemy : public Enemy
	{
		REGISTER_TYPE_H(FlyingEnemy);
		REGISTER_ACTOR_H(FlyingEnemy);
		
	public:
		void start() override;
		json serialize() override;
		void deserialize(json j) override;

	protected:
		void aggro(Tristeon::Player* player) override;
		void patrol() override;
		void die() override;

		Tristeon::Vector2 startPos;
		int direction = 1;
		float patrolSpeed = 0;
		float chaseSpeed = 0;
		float patrolDistance = 0;
		float goalDetectDistance = 0;
	};
}

#ifdef TRISTEON_EDITOR
#include <Editor/Dynamic/Objects/Actors/AnimationSpriteEditor.h>

namespace DemoEditor
{
	class FlyingEnemyEditor : public TristeonEditor::AnimationSpriteEditor
	{
		OBJECT_EDITOR_H(Demo::FlyingEnemy, FlyingEnemyEditor);
	};
}
#endif