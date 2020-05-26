#include "Weapon.h"

#include "Input/Mouse.h"
#include "Rendering/GameView.h"
#include "Scenes/Scene.h"
#include "Scenes/SceneManager.h"
#include <Scenes/Layers/ActorLayer.h>

#include "Demo/Projectile.h"
#include "Input/Keyboard.h"

namespace Demo
{
	REGISTER_TYPE_CPP(Weapon);
	REGISTER_BEHAVIOUR_CPP(Weapon);
	
	json Weapon::serialize()
	{
		json j;
		j["typeID"] = TRISTEON_TYPENAME(Weapon);
		j["chargeDuration"] = chargeDuration;
		j["minimumCharge"] = minimumCharge;
		j["throwStrength"] = throwStrength;
		j["throwStrengthY"] = throwStrengthY;
		j["damage"] = damage;
		return j;
	}

	void Weapon::deserialize(json j)
	{
		chargeDuration = j.value("chargeDuration", 0);
		minimumCharge = j.value("minimumCharge", 0.1f);
		throwStrength = j.value("throwStrength", 0);
		throwStrengthY = j.value("throwStrengthY", 0);
		damage = j.value("damage", 0);
	}

	void Weapon::start()
	{
		chargeBar = dynamic_cast<Tristeon::AnimationSprite*>(Tristeon::Actor::find("ChargeBar"));
		chargeBar->setPaused(true);
	}

	void Weapon::update()
	{
		if (Tristeon::Keyboard::pressed(Tristeon::Keyboard::Space))
			charging = true;
		
		if (Tristeon::Keyboard::released(Tristeon::Keyboard::Space))
		{
			if (charging)
				shoot(std::max(time / chargeDuration, minimumCharge));
			
			charging = false;
		}

		chargeBar->display = charging;
		chargeBar->position = getOwner()->position + Tristeon::Vector2::up() * 64;
		
		if (charging)
		{
			time += Tristeon::GameView::deltaTime() * 2;
			chargeBar->setFrame(int((time / 1000)* 4.0f));
			if (time >= chargeDuration)
				shoot(1);
		}
	}

	void Weapon::shoot(float strength)
	{
		time = 0;
		int direction = getOwner<Tristeon::Player>()->flipX ? -1 : 1;
		Tristeon::ActorLayer* layer = Tristeon::SceneManager::current()->findLayerOfType<Tristeon::ActorLayer>();

		auto* projectile = layer->createActor<Projectile>();
		projectile->position = getOwner()->position + Tristeon::Vector2(getOwner<Tristeon::Player>()->width * direction, getOwner<Tristeon::Player>()->width / 4.0f);
		projectile->setTexture("Project/Bullet.png", true);
		projectile->addBehaviour<Tristeon::PhysicsBody>();
		Tristeon::CircleCollider* collider = projectile->addBehaviour<Tristeon::CircleCollider>();
		collider->radius(projectile->width / 2.0f);
		projectile->source = getOwner<Tristeon::Player>();
		projectile->damage = damage * strength;
		projectile->start();
		projectile->shoot(direction, strength * throwStrength, throwStrengthY);
	}
}
