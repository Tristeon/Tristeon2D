#include "Glider.h"

#include "Input/Keyboard.h"
#include "Math/Math.h"
#include "Player.h"

namespace Demo
{
	REGISTER_TYPE_CPP(Glider);
	REGISTER_BEHAVIOUR_CPP(Glider);

	json Glider::serialize()
	{
		json j;
		j["typeID"] = TRISTEON_TYPENAME(Glider);
		j["maximumYVelocity"] = maximumYVelocity;
		return j;
	}

	void Glider::deserialize(json j)
	{
		maximumYVelocity = j.value("maximumYVelocity", 0);
	}

	void Glider::update()
	{
		gliding = !getOwner<Tristeon::Player>()->movementBehaviour->isGrounded && Tristeon::Keyboard::held(Tristeon::Keyboard::C);

		if (gliding)
		{
			Tristeon::PhysicsBody* pb = getOwner<Tristeon::Player>()->physicsBody;
			pb->setVelocity(pb->velocity().x, Tristeon::Math::clamp(pb->velocity().y, -maximumYVelocity, maximumYVelocity));
		}
	}
}
