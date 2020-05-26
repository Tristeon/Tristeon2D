#include "IgnoreCameraMovement.h"


#include "Actors/Actor.h"
#include "Serialization/Typename.h"

namespace Demo
{
	REGISTER_TYPE_CPP(IgnoreCameraMovement);
	REGISTER_BEHAVIOUR_CPP(IgnoreCameraMovement);
	
	json IgnoreCameraMovement::serialize()
	{
		json j;
		j["typeID"] = TRISTEON_TYPENAME(IgnoreCameraMovement);
		return j;
	}

	void IgnoreCameraMovement::deserialize(json j)
	{
		
	}

	void IgnoreCameraMovement::lateUpdate()
	{
		getOwner()->position = positionOffset + (Tristeon::Vector2)Tristeon::Camera::main()->position;
	}

	void IgnoreCameraMovement::start()
	{
		positionOffset = getOwner()->position;
	}
}