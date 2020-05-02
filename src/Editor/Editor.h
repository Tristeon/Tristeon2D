#pragma once
#ifdef TRISTEON_EDITOR
#include <Editor/EditorWindow.h>
#include <Editor/MenuBar.h>

#include <Actors/Actor.h>
#include <Utils/Delegate.h>

namespace TristeonEditor
{
	class Editor
	{
	public:
		void initialize();
		void addWindow(EditorWindow* window);

		Tristeon::Layer* selectedLayer() const;
		void selectedLayer(Tristeon::Layer* value);

		Tristeon::Actor* selectedActor() const;
		void selectedActor(Tristeon::Actor* value);

		Tristeon::Delegate<Tristeon::String> onSelectedActorNameChanged;
		
		void setMenuBar(MenuBar* menu_bar);

	private:
		Tristeon::Layer* _selectedLayer = nullptr;
		Tristeon::Actor* _selectedActor = nullptr;
		MenuBar* menuBar = nullptr;
		Tristeon::Vector<EditorWindow*> windows;
	};
}
#endif