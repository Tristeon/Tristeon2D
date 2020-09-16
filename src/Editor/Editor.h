#pragma once
#ifdef TRISTEON_EDITOR
#include "AssetExplorer/Importer.h"
#include "Utils/Singleton.h"

#include <Editor/DockWidget.h>
#include <Editor/MenuBar.h>

#include <Scenes/Actors/Actor.h>
#include <Utils/Delegate.h>

namespace TristeonEditor
{
	struct FileItem;

	class Editor : public Tristeon::Singleton<Editor>
	{
	public:
		void initialize();
		void addWidget(DockWidget* window);

		Tristeon::Layer* selectedLayer() const;
		void selectedLayer(Tristeon::Layer* value);

		Tristeon::Actor* selectedActor() const;
		void selectedActor(Tristeon::Actor* value);

		FileItem* selectedFileItem() const;
		void selectedFileItem(FileItem* value);

		Tristeon::Delegate<Tristeon::String> onSelectedActorNameChanged;
		
		void setMenuBar(MenuBar* menu_bar);

	private:
		Tristeon::Layer* _selectedLayer = nullptr;
		Tristeon::Actor* _selectedActor = nullptr;
		FileItem* _selectedFileItem = nullptr;
		MenuBar* menuBar = nullptr;
		Importer importer;
		Tristeon::Vector<DockWidget*> windows;
	};
}
#endif