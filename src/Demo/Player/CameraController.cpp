#include "CameraController.h"
#include "Actors/Actor.h"
#include "Scenes/Camera.h"

namespace Demo
{
	REGISTER_TYPE_CPP(CameraController)
	REGISTER_BEHAVIOUR_CPP(CameraController)
	
	json CameraController::serialize()
	{
		json j;
		j["typeID"] = TRISTEON_TYPENAME(CameraController);
		return j;
	}

	void CameraController::deserialize(json j)
	{
		//Empty
	}

	void CameraController::lateUpdate()
	{
		Tristeon::Camera::main()->position = (Tristeon::Vector2Int)getOwner()->position;
	}
}
