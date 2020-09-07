#ifdef TRISTEON_EDITOR
#include "Window.h"
#include "Actors/Camera.h"
#include "Editor/GameView.h"
#include "Math/Math.h"
#include "Rendering/Gizmos.h"
#include "Rendering/Grid.h"
#include "Input/Keyboard.h"
#include "Actors/Sprite.h"
#include "Engine.h"
#include "ActorLayerSceneView.h"
#include "Rendering/Graphic.h"
#include "Editor/Editor.h"
#include <Input/Mouse.h>

using namespace Tristeon;
namespace TristeonEditor
{
	SCENE_EDITOR_CPP(Tristeon::ActorLayer, ActorLayerSceneView);
	
	void ActorLayerSceneView::initialize()
	{
		actorLayer = dynamic_cast<ActorLayer*>(target());
	}

	void ActorLayerSceneView::updateView()
	{
		if (Engine::playMode())
		{
			dragging = false;
			draggingScalar = false;
			draggingRotate = false;
			return;
		}

		if (Mouse::pressed(Mouse::Left) && GameView::instance()->underMouse())
		{
			if (scalar.underMouse())
				draggingScalar = true;
			else if (rotator.underMouse())
				draggingRotate = true;
			else
				clickActor();
		}
		else if (Mouse::held(Mouse::Left) && Editor::instance()->selectedActor() != nullptr && !Keyboard::held(Keyboard::Alt))
		{
			if (dragging)
			{
				if (Keyboard::held(Keyboard::Shift))
				{
					auto* graphic = dynamic_cast<Graphic*>(Editor::instance()->selectedActor());
					if (graphic == nullptr)
						Editor::instance()->selectedActor()->position = Grid::snap(Window::screenToWorld(Mouse::position()) - draggingOffset);
					else
						graphic->position = Grid::snap(Window::screenToWorld(Mouse::position()) - draggingOffset) + graphic->bounds().size() / 2.0f - Grid::tileSize() / 2.0f;
				}
				else
					Editor::instance()->selectedActor()->position = Window::screenToWorld(Mouse::position()) - draggingOffset;
			}
			else if (draggingScalar)
			{
				//TODO: Make graphic resizing more generic
				auto* sprite = dynamic_cast<Sprite*>(Editor::instance()->selectedActor());

				if (sprite != nullptr && sprite->texture() != nullptr)
				{
					Vector2 const position = Editor::instance()->selectedActor()->position;
					Vector2 const topRight = Window::screenToWorld(Mouse::position());
					Vector2 const difference = topRight - position;
					if (difference.x < 0 || difference.y < 0)
						return;

					Vector2 size = difference / sprite->scale * 2;

					//Snap to aspect ratio
					if (Keyboard::held(Keyboard::Shift))
					{
						Vector2 const imageSize = sprite->texture()->size();
						
						if (size.x > size.y) //Prioritize X
							size.x = imageSize.x / imageSize.y * size.y;
						else //Prioritize Y
							size.y = imageSize.y / imageSize.x * size.x;
					}
					
					sprite->width = size.x;
					sprite->height = size.y;
				}
			}
			else if (draggingRotate)
			{
				Vector2 const position = Editor::instance()->selectedActor()->position;
				Vector2 const mouse = (Window::screenToWorld(Mouse::position()) - position).getNormalized();
				const float angle = mouse.getAngle();

				if (Keyboard::held(Keyboard::Shift))
					Editor::instance()->selectedActor()->rotation = roundf(angle / 45.0f) * 45.0f;
				else
					Editor::instance()->selectedActor()->rotation = angle;
			}
		}
		else if (Mouse::released(Mouse::Left))
		{
			dragging = false;
			draggingScalar = false;
			draggingRotate = false;
			Editor::instance()->selectedActor(Editor::instance()->selectedActor());
		}
		
		auto* graphic = dynamic_cast<Graphic*>(Editor::instance()->selectedActor());
		if (graphic != nullptr)
		{
			Graphic::Bounds const aabb = graphic->bounds();
			Gizmos::drawSquare(graphic->position, aabb.size(), graphic->rotation, Colour(0.5, 0.5, 1, 1));

			const Vector2 handleSize = Vector2(Math::clamp(32 / Renderer::editorCamera()->zoom, 8, 256), Math::clamp(32 / Renderer::editorCamera()->zoom, 8, 256));
			const Vector2 cpos = Math::orbit(graphic->position, aabb.size() / 2.0f, graphic->rotation);
			Gizmos::drawSquare(cpos, handleSize, graphic->rotation, Colour(0.5, 0.5, 0.5));
			scalar = Graphic::Bounds{ cpos - handleSize / 2.0f, cpos + handleSize / 2.0f };

			const Vector2 rpos = Math::orbit(graphic->position, Vector2(aabb.size().x, 0), graphic->rotation);
			Gizmos::drawSquare(rpos, handleSize, graphic->rotation, Colour(0, 0.5, 0.5));
			rotator = Graphic::Bounds{ rpos - handleSize / 2.0f, rpos + handleSize / 2.0f };
		}
		else
		{
			dragging = false;
			draggingScalar = false;
			draggingRotate = false;
		}
	}

	void ActorLayerSceneView::clickActor()
	{
		Vector2 const world = Window::screenToWorld(Mouse::position());
		for (size_t i = 0; i < actorLayer->getActorCount(); i++)
		{
			auto* graphic = dynamic_cast<Graphic*>(actorLayer->getActor(i));

			if (graphic != nullptr)
			{
				if (graphic->bounds().contains(world))
				{
					if (graphic == Editor::instance()->selectedActor())
					{
						dragging = true;
						draggingOffset = world - graphic->position;
					}

					Editor::instance()->selectedActor(graphic);
					return;
				}
			}
		}

		Editor::instance()->selectedActor(nullptr);
		dragging = false;
		draggingScalar = false;
		draggingRotate = false;
	}
}
#endif