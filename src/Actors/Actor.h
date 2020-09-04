#pragma once
#include "Serialization/InstancedSerializable.h"

#include <Actors/Behaviours/Behaviour.h>

#include "Callbacks/IStart.h"
#include "Math/Vector2.h"
#include <Scenes/Scene.h>
#include <Scenes/SceneManager.h>

namespace Tristeon
{
	class SceneManager;

	template<typename T>
	using IsBehaviour = std::enable_if_t<std::is_base_of<Behaviour, T>::value, T>;

	/**
	 * An actor is an empty container that can exist freely on an ActorLayer.
	 * Actors can be inherited from to implement more specific actors such as Player, Car, Enemy, etc.
	 * In addition to that, you can add Behaviours to actors, providing extra flexibility and re usability.
	 *
	 * Within Tristeon, we recommend to make the core object-defining classes such as Enemy or Gun derived classes of Actor,
	 * while additional and potentially reusable behaviours such as a FollowBehaviour should be added as Behaviours.
	 * 
	 * Unlike Tiles, Actors can move, scale and rotate around the level freely, unbound by the grid or by axis alignment.
	 */
	class Actor : public InstancedSerializable
	{
		friend ActorLayer;
		friend SceneManager;
		friend class Engine;
	public:
		/**
		 * The current position in 2D space of the actor, in pixels.
		 */
		Vector2 position = { 0, 0 };

		/**
		 * The current scale of the actor, Vector2::one() by default.
		 */
		Vector2 scale = { 1, 1 };

		/**
		 * The current rotation of the actor, in degrees.
		 */
		float rotation = 0;

		/**
		 * The name of the actor, used to identify the actor.
		 */
		std::string name = "";

		Actor();
		virtual ~Actor() noexcept;
		
		json serialize() override;
		void deserialize(json j) override;

		/**
		 * Gets the first behaviour of type T. nullptr if no behaviour of type T was found.
		 */
		template<typename T>
		IsBehaviour<T>* getBehaviour();

		/**
		 * Gets a list of all the behaviours of type T. Returns an empty list if no behaviour of type T was found.
		 */
		template<typename T>
		Vector<T*> getBehaviours();

		/**
		 * Gets a list with all of the actor's behaviours.
		 */
		Vector<Behaviour*> getBehaviours();
		
		/**
		 * Adds a new behaviour of type T and returns the new behaviour.
		 */
		template<typename T>
		IsBehaviour<T>* addBehaviour();

		Behaviour* addBehaviour(std::string type);

		/**
		 * Destroy removes the actor from the scene and deletes the Actor's instance.
		 * destroy() should be used at all times as opposed to manual deletion, to avoid deleting objects within critical loops.
		 */
		void destroy();

		/**
		 * Looks through every actor layer,
		 * returns the first actor with the given name.
		 *
		 * Returns nullptr if no actor was found.
		 */
		static Actor* find(String const& name);

		/**
		 * Looks through every actor layer,
		 * returns the actor with the given ID.
		 *
		 * Returns nullptr if no such actor exists.
		 */
		static Actor* find(unsigned int const& id);

		/**
		 * Looks through every actor layer,
		 * returns the first actor with the given type.
		 *
		 * Returns nullptr if no actor was found.
		 */
		template<typename T>
		static T* findOfType();

		/**
		 * Looks through every actor layer,
		 * returns the first actor with the given type AND name.
		 *
		 * Returns nullptr if no actor was found.
		 */
		template<typename T>
		static T* findOfType(String name);
	private:
		Vector<Unique<Behaviour>> _behaviours{};
		bool destroyed = false;

		/**
		 * Removes and destroys the given behaviour.
		 * Used internally by Engine to destroy behaviours outside of critical loops.
		 */
		void removeBehaviour(Behaviour* behaviour);
	};

	template <typename T>
	IsBehaviour<T>* Actor::getBehaviour()
	{
		for (auto const& behaviour : _behaviours)
		{
			T* result = dynamic_cast<T*>(behaviour.get());
			if (result != nullptr)
				return result;
		}
		return nullptr;
	}

	template <typename T>
	Vector<T*> Actor::getBehaviours()
	{
		Vector<T*> behaviours;

		for (auto const& behaviour : _behaviours)
		{
			T* value = dynamic_cast<T*>(behaviour.get());
			if (value != nullptr)
				behaviours.add(value);
		}

		return behaviours;
	}

	template <typename T>
	IsBehaviour<T>* Actor::addBehaviour()
	{
		T* result = new T();
		result->_owner = this;
		_behaviours.add(Unique<Behaviour>(result));

		//Call start callback if available.
		IStart* istart = dynamic_cast<IStart*>(result);
		if (istart != nullptr)
			istart->start();
		
		return result;
	}

	template <typename T>
	T* Actor::findOfType()
	{
		auto actors = Collector<Actor>::all();
		for (auto actor : actors)
		{
			if (dynamic_cast<T*>(actor))
				return (T*)actor;
		}
		return nullptr;
	}

	template <typename T>
	T* Actor::findOfType(String name)
	{
		auto actors = Collector<Actor>::all();
		for (auto actor : actors)
		{
			if (actor->name == name && dynamic_cast<T*>(actor))
				return (T*)actor;
		}
		return nullptr;
	}
}
