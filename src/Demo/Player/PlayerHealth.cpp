#include "PlayerHealth.h"

#include "Demo/Enemies/Enemy.h"
#include "Physics/Collider.h"
#include "Player.h"
#include "Rendering/GameView.h"
#include "Scenes/SceneManager.h"

namespace Demo
{
	REGISTER_TYPE_CPP(PlayerHealth);
	REGISTER_BEHAVIOUR_CPP(PlayerHealth);
	
	json PlayerHealth::serialize()
	{
		json j;
		j["typeID"] = TRISTEON_TYPENAME(PlayerHealth);
		j["maxHealth"] = maxHealth;
		return j;
	}

	void PlayerHealth::deserialize(json j)
	{
		maxHealth = j.value("maxHealth", 0);
	}

	void PlayerHealth::start()
	{
		currentHealth = maxHealth;

		healthBar = Tristeon::Actor::findOfType<Tristeon::AnimationSprite>("HealthBar");
		healthBar->setPaused(true);
		healthBar->setFrame(0);
	}

	void PlayerHealth::update()
	{
		if (fade > 0)
		{
			fade -= Tristeon::GameView::deltaTime() / 1000.0f;
			getOwner<Tristeon::Player>()->colour.a = fade;

			if (fade < 0)
			{
				if (currentHealth > 0)
				{
					getOwner<Tristeon::Player>()->colour.a = 1;
					
					getOwner<Tristeon::Player>()->unfreeze();
					getOwner<Tristeon::Player>()->respawn();
				}
				else
				{
					Tristeon::SceneManager::reload();
				}
			}
		}
	}

	void PlayerHealth::contactBegin(Tristeon::Collider* other)
	{
		if (fade > 0)
			return;
		
		if (other->getOwner<Enemy>())
		{
			takeHit();
		}
	}

	void PlayerHealth::takeHit()
	{
		if (fade > 0)
			return;

		currentHealth--;
		fade = 1;

		healthBar->setFrame(maxHealth - currentHealth);
		getOwner<Tristeon::Player>()->freeze();
	}
}
