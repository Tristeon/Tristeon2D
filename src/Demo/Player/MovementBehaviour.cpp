#include "MovementBehaviour.h"
#include "Actors/Actor.h"
#include "Input/Keyboard.h"
#include "Physics/Collider.h"
#include "Physics/PhysicsWorld.h"
#include "Player.h"
#include "Rendering/GameView.h"

namespace Tristeon
{
	REGISTER_TYPE_CPP(MovementBehaviour);
	REGISTER_BEHAVIOUR_CPP(MovementBehaviour);
	
	void MovementBehaviour::update()
	{
		isGrounded = PhysicsWorld::raycast(getOwner()->position, Vector2::down(), groundCheckDistance);

		Vector2 velocity = getOwner<Player>()->physicsBody->velocity();
		
		if (isGrounded && Keyboard::pressed(Keyboard::Up))
			velocity.y = jumpSpeed;
		
		float const horizontal = Keyboard::held(Keyboard::Right) - Keyboard::held(Keyboard::Left);
		velocity.x = horizontal * movementSpeed;

		getOwner<Player>()->physicsBody->setVelocity(velocity);
	}

	json MovementBehaviour::serialize()
	{
		json j;
		j["typeID"] = TRISTEON_TYPENAME(MovementBehaviour);
		j["movementSpeed"] = movementSpeed;
		j["jumpSpeed"] = jumpSpeed;
		j["groundCheckDistance"] = groundCheckDistance;
		return j;
	}

	void MovementBehaviour::deserialize(json j)
	{
		movementSpeed = j["movementSpeed"];
		jumpSpeed = j["jumpSpeed"];
		groundCheckDistance = j["groundCheckDistance"];
	}

	void MovementBehaviour::contactBegin(Collider* other)
	{
	}

	void MovementBehaviour::contactEnd(Collider* other)
	{
	}

	void MovementBehaviour::tileContactBegin(TileContact const& contact)
	{
	}

	void MovementBehaviour::tileContactEnd(TileContact const& contact)
	{
	}
}
