#pragma once
#include "Types.h"
#include "Polygon.h"
#include "Circle.h"
namespace Game
{
	struct window_t {
		GLint width, height;
	} static window;

	struct mouse_t
	{
		Circle circle;
		coord2d coord;
	} static mouse;

	void Init(char* title, int width, int height, bool fullScreen);
	void setFullScreen(bool b);
	bool getFullScreen();
	void toggleFullScreen();

	void mainRender();
	void mouseLeftDown(coord2d c);

	void write(const char * s, coord2d coord, colorRGB color);
}