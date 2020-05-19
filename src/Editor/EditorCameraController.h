#pragma once
#include "Editor.h"
#ifdef TRISTEON_EDITOR
namespace TristeonEditor
{
	class EditorCameraController
	{
		friend class GameViewEditor;
		
	public:
		void update();
	private:
		void handleDragging();
		void handleScrolling();
		
		bool dragging = false;
		Editor* editor = nullptr;
		Tristeon::Vector2Int dragMousePos;
	};
}
#endif