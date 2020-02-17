/*
	MIT License

	Copyright (c) 2017 Tristan Metz, Leon Brands

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#include <QApplication>
#include <QWidget>

#include "Engine.h"

#ifndef TRISTEON_LOGENABLED
#include <Windows.h>
#endif

#ifdef TRISTEON_EDITOR
//#include <Editor/Editor.h>
#endif

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

#ifndef TRISTEON_LOGENABLED
	FreeConsole();
#endif

	Tristeon::Engine engine{};

#ifdef TRISTEON_EDITOR
	//TristeonEditor::Editor editor{};
#else
	//TODO: Auto start game with the starting scene loaded in in game/release mode
#endif

	engine.run();
	return 0;
}