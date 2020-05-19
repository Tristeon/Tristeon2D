#pragma once
#include "Behaviour.h"
#include <Serialization/TypeRegister.h>
#include <Registers/BehaviourRegister.h>

#include "Actors/Player.h"
#include "Callbacks/IUpdate.h"
#include "Physics/Callbacks/IContactBegin.h"
#include "Physics/Callbacks/IContactEnd.h"
#include "Physics/Callbacks/ITileContactBegin.h"
#include "Physics/Callbacks/ITileContactEnd.h"

namespace Tristeon
{
	class MovementBehaviour : public Behaviour, public IUpdate, public IContactBegin, public IContactEnd, public ITileContactBegin, public ITileContactEnd
	{
		REGISTER_BEHAVIOUR_H(MovementBehaviour)
			REGISTER_TYPE_H(MovementBehaviour)
	public:
		MovementBehaviour() = default;
		virtual ~MovementBehaviour() = default;

		void update() override;

		json serialize() override;
		void deserialize(json j) override;

		void contactBegin(Collider* other) override;
		void contactEnd(Collider* other) override;
		void tileContactBegin(TileContact const& contact) override;
		void tileContactEnd(TileContact const& contact) override;

		bool isGrounded = false;
	private:

		//Player* getPlayer() const;
		float groundCheckDistance = 32;
		float movementSpeed = 0;
		float jumpSpeed = 0;
	};
}
