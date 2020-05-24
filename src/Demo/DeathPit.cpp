#include "DeathPit.h"
#include "Player/Player.h"
#include "Scenes/SceneManager.h"

namespace Demo
{
	REGISTER_TYPE_CPP(DeathPit);
	REGISTER_ACTOR_CPP(DeathPit);
	
	void DeathPit::contactBegin(Tristeon::Collider* other)
	{
		if (other->getOwner<Tristeon::Player>() != nullptr)
		{
			Tristeon::SceneManager::reload();
		}
	}

	json DeathPit::serialize()
	{
		json j = Sprite::serialize();
		j["typeID"] = TRISTEON_TYPENAME(DeathPit);
		return j;
	}
}

#ifdef TRISTEON_EDITOR
namespace DemoEditor
{
	OBJECT_EDITOR_CPP(Demo::DeathPit, DeathPitEditor);
}
#endif