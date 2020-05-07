#ifdef TRISTEON_EDITOR
#include "TileLayerEditor.h"
#include <Serialization/JsonSerializer.h>

using Tristeon::Vector2;
using Tristeon::Vector2Int;

namespace TristeonEditor
{
	OBJECT_EDITOR_CPP(Tristeon::TileLayer, TileLayerEditor)

	void TileLayerEditor::initialize()
	{
		setMouseTracking(true);
		
		auto* formParent = new QWidget(this);
		formParent->show();
		layout->addWidget(formParent);
		
		auto* form = new QFormLayout();
		formParent->setLayout(form);
		
		//Width Field
		auto* widthText = new QLabel("Width", formParent);
		widthText->show();

		auto* widthField = new QSpinBox(formParent);
		widthField->setMinimum(1);
		widthField->setMaximum(std::numeric_limits<int>::max());
		widthField->setSingleStep(1);
		widthField->setValue(targetLayer->width());
		widthField->show();
		connect(widthField, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged) /* connect can't infer without the cast coz of ambiguity*/, this, &TileLayerEditor::mapWidthChanged);

		form->addRow(widthText, widthField);
		
		//Height Field
		auto* heightText = new QLabel("Height", formParent);
		heightText->show();

		auto* heightField = new QSpinBox(formParent);
		heightField->setMinimum(1);
		heightField->setMaximum(std::numeric_limits<int>::max());
		heightField->setSingleStep(1);
		heightField->setValue(targetLayer->height());
		heightField->show();
		connect(heightField, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &TileLayerEditor::mapHeightChanged);

		form->addRow(heightText, heightField);
	}

	void TileLayerEditor::targetChanged(Tristeon::TObject* current, Tristeon::TObject* old)
	{
		targetLayer = dynamic_cast<Tristeon::TileLayer*>(current);
	}

	void TileLayerEditor::mapWidthChanged(int width)
	{
		resizeMap(width, targetLayer->height());
	}

	void TileLayerEditor::mapHeightChanged(int height)
	{
		resizeMap(targetLayer->width(), height);
	}

	void TileLayerEditor::resizeMap(int width, int height)
	{
		json j = targetLayer->serialize();

		int const oldWidth = j["width"];
		int const oldHeight = j["height"];
		json oldData = j["data"];
		
		j["data"] = json::array_t(width * height);
		j["width"] = width;
		j["height"] = height;
		for (int x = 0; x < width; x++)
		{
			for (int y = 0; y < height; y++)
			{
				int const index = y * width + x;

				if (x < oldWidth && y < oldHeight)
					j["data"][index] = oldData[y * oldWidth + x];
				else
					j["data"][index] = -1;
			}
		}
		targetLayer->deserialize(j);
	}
}
#endif