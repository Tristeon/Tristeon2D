#ifdef TRISTEON_EDITOR
#include "Editor.h"
#include "Window.h"

#include <Scenes/Scene.h>

namespace TristeonEditor
{
	void Editor::initialize()
	{
		//Scan meta files
		importer.scanAssets();
		
		if (menuBar != nullptr)
			menuBar->initialize();
		
		//Initialize windows
		for (auto* window : windows)
			window->initialize();
	}

	void Editor::addWidget(DockWidget* window)
	{
		windows.add(window);
	}

	Tristeon::Layer* Editor::selectedLayer() const
	{
		return _selectedLayer;
	}

	void Editor::selectedLayer(Tristeon::Layer* value)
	{
		_selectedLayer = value;

		selectedActor(nullptr);
		
		for (auto* window : windows)
			window->selectedLayerChanged(value);
	}

	Tristeon::Actor* Editor::selectedActor() const
	{
		return _selectedActor;
	}

	void Editor::selectedActor(Tristeon::Actor* value)
	{
		_selectedActor = value;

		for (auto* window : windows)
			window->selectedActorChanged(value);
	}

	FileItem* Editor::selectedFileItem() const
	{
		return _selectedFileItem;
	}

	void Editor::selectedFileItem(FileItem* value)
	{
		_selectedFileItem = value;

		for (auto* window : windows)
			window->selectedFilePathChanged(value);
	}

	void Editor::setMenuBar(MenuBar* menu_bar)
	{
		menuBar = menu_bar;
	}

	void Editor::sceneLoaded(Tristeon::Scene* scene)
	{
		Tristeon::Window::setWindowTitle("Tristeon2D | " + scene->name());
		selectedLayer(nullptr);

		for (auto* window : windows)
			window->sceneLoaded(scene);
	}
}
#endif