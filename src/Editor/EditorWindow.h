#pragma once
#include "Actors/Behaviours/Behaviour.h"
#ifdef TRISTEON_EDITOR
#include <Scenes/Scene.h>

namespace TristeonEditor
{
	class EditorWindow
	{
		friend class Editor;
	public:
		EditorWindow() = default;
		virtual ~EditorWindow() = default;

	protected:
		virtual void initialize() = 0;
		virtual void sceneLoaded(Tristeon::Scene* scene) = 0;
		virtual void selectedLayerChanged(Tristeon::Layer* layer) { /* Empty */ }
		virtual void selectedActorChanged(Tristeon::Actor* actor) { /* Empty */ }

		Editor* editor = nullptr;
	};
}
#endif