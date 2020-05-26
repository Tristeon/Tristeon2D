#include "DamageText.h"

#include "Actors/AnimationSprite.h"
#include "Math/Vector2.h"
#include "Rendering/GameView.h"
#include "Scenes/Layers/ActorLayer.h"

namespace Demo
{
	void DamageText::drawDamage(Tristeon::Vector2 const& position, int const& amount)
	{
		Tristeon::ActorLayer* layer = dynamic_cast<Tristeon::ActorLayer*>(Tristeon::SceneManager::current()->findLayer("Objects"));
		
		int xOffset = 0;
		if (amount >= 100)
		{
			int const hundreds = amount / 100;

			auto* text = layer->createActor<DamageText>();
			text->position = position;
			text->width = 64;
			text->height = 64;
			text->setAnimationClip("Project/Numbers.clip");
			text->setPaused(true);
			text->setFrame(hundreds);
			xOffset += 64 + 16;
		}

		if (amount >= 10)
		{
			int const tens = (amount % 100) / 10;
			auto* text = layer->createActor<DamageText>();
			text->position = position + Tristeon::Vector2((float)xOffset, 0);
			text->width = 64;
			text->height = 64;
			text->setAnimationClip("Project/Numbers.clip");
			text->setPaused(true);
			text->setFrame(tens);
			xOffset += 64 + 16;
		}

		int const singles = (amount % 10);
		auto* text = layer->createActor<DamageText>();
		text->position = position + Tristeon::Vector2((float)xOffset, 0);
		text->width = 64;
		text->height = 64;
		text->setAnimationClip("Project/Numbers.clip");
		text->setPaused(true);
		text->setFrame(singles);
	}

	void DamageText::update()
	{
		destroyTimer += Tristeon::GameView::deltaTime();
		colour.a = 1 - destroyTimer / 500.0f;
		if (destroyTimer >= 500)
			destroy();
	}
}
