#pragma once
#include "Types.h"
#include "Polygon.h"
#include "Circle.h"
namespace Game
{
	struct window_t {
		int width, height;
	} static window;

	struct mouse_t
	{
		Circle circle;
		coord2d coord;
	} static mouse;

	void Init(char* title, int width, int height, bool fullScreen);
	void mainRender();
	void setFullScreen(bool b);
	bool getFullScreen();
	void toggleFullScreen();
	void write(const char * s, coord2d coord, colorRGB color);
}