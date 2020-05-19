#include "NextLevelSign.h"
#include "Physics/Collider.h"
#include "Player.h"
#include "Scenes/SceneManager.h"

namespace Demo
{
	REGISTER_TYPE_CPP(NextLevelSign);
	REGISTER_BEHAVIOUR_CPP(NextLevelSign);

	json NextLevelSign::serialize()
	{
		json j;
		j["typeID"] = TRISTEON_TYPENAME(NextLevelSign);
		j["nextScene"] = nextScene;
		return j;
	}

	void NextLevelSign::deserialize(json j)
	{
		nextScene = j["nextScene"].get<Tristeon::String>();
	}

	void NextLevelSign::sensorBegin(Tristeon::Collider* other)
	{
		if (dynamic_cast<Tristeon::Player*>(other->getOwner()) != nullptr)
		{
			Tristeon::SceneManager::load(nextScene);
		}
	}
}
