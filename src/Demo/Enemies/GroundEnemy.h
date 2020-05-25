#pragma once
#include "Enemy.h"

namespace Demo
{
	class GroundEnemy : public Enemy
	{
		REGISTER_TYPE_H(GroundEnemy);
		REGISTER_ACTOR_H(GroundEnemy);
		
		enum PatrolDirection
		{
			Left = -1,
			Right = 1
		};
		
	public:
		json serialize() override;
		void deserialize(json j) override;

	protected:
		void aggro(Tristeon::Player* player) override;
		void patrol() override;
		void die() override;

		int patrolDirection = Left;
		float patrolSpeed = 0;
		float chaseSpeed = 0;
		float wallCheckDistance = 0;
		float floorCheckDistance = 0;
		float floorCheckOffset = 0;
	};
}

#ifdef TRISTEON_EDITOR
#include <Editor/Dynamic/Objects/Actors/AnimationSpriteEditor.h>

namespace DemoEditor
{
	class GroundEnemyEditor : public TristeonEditor::AnimationSpriteEditor
	{
		OBJECT_EDITOR_H(Demo::GroundEnemy, GroundEnemyEditor);
	};
}
#endif