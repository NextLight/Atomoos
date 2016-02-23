#pragma once
#include "Types.h"
#include "Polygon.h"
#include "Circle.h"
namespace Game
{
	 struct window_t {
		GLint width, height;
	};

	 struct mouse_t {
		Circle circle;
		coord2d coord;
	};

	void Init(char* title, int width, int height, bool fullScreen);
	void setFullScreen(bool b);
	bool getFullScreen();
	void toggleFullScreen();

	void mainRender();
	void mouseLeftDown(coord2d c);

	void write(const char * s, coord2d coord, colorRGB color);

	extern window_t window;
	extern mouse_t mouse;
}