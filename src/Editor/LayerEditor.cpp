#ifdef TRISTEON_EDITOR
#include "Scenes/Layers/Layer.h"
#include "LayerEditor.h"
#include "Editor.h"
#include "CustomEditors/EditorRegister.h"

namespace TristeonEditor
{
	void LayerEditor::initialize()
	{
		layout = new QGridLayout();
		layout->setContentsMargins(0, 0, 0, 0);
		contents = findChild<QWidget*>("contents");
		contents->setLayout(layout);
		contents->show();
		
		if (editor->selectedLayer() != nullptr)
			selectedLayerChanged(editor->selectedLayer());
	}

	void LayerEditor::sceneLoaded(Tristeon::Scene* scene)
	{
		
	}

	void LayerEditor::selectedLayerChanged(Tristeon::Layer* layer)
	{
		if (current != nullptr)
		{
			layout->removeWidget(current);
			current->deleteLater();
		}
		current = nullptr;
		
		if (layer == nullptr)
			return;

		current = EditorRegister::createInstance(layer->serialize()["typeID"]);
		if (current != nullptr)
		{
			current->editor(editor);
			current->target(layer);
			current->setParent(contents);
			current->initialize();
			layout->addWidget(current);
			current->show();
		}
	}
}
#endif