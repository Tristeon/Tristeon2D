#pragma once
#include <memory>

#include <Rendering/Renderer.h>
#include <Physics/PhysicsWorld.h>

#include <TypeDefinitions.h>
#include <Utils/Singleton.h>

namespace Tristeon
{
	/**
	 * Engine is the absolute core of Tristeon. It owns engine subsystems such as Renderer, GameView, Physics, etc.
	 * It manages the creation and destruction of the engine subsystems. Subsystems may be accessible through their own Singleton instances.
	 */
	class Engine final : private Singleton<Engine>
	{
		friend Singleton<Engine>;

		friend Actor;
		friend Behaviour;
		
	public:
		Engine() = default;
		Engine(Engine const& other) = delete;
		void operator=(Engine const& other) = delete;
		void run();

		/**
		 * Enables or disables the play-mode, usually adjusted by the editor.
		 */
		static void playMode(bool const& enabled);

		/**
		 * Gets if the engine is in play-mode or not.
		 */
		static bool playMode();
		
		void destroyLater(Actor* actor);
		void destroyLater(Behaviour* behaviour);
	private:
		bool inPlayMode = false;
		bool playModeDirty = false;
		Unique<Renderer> _renderer = nullptr;
		Unique<PhysicsWorld> _physics = nullptr;

		Vector<Actor*> destroyedActors{};
		Vector<Behaviour*> destroyedBehaviours{};

		void processDestroyedObjects();
	};
}