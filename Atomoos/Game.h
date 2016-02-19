#pragma once
#include "Types.h"
#include "Polygon.h"
#include "Circle.h"
//#include "mouse.h"
namespace Game
{
	struct window_t {
		int width, height;
	} static window;

	struct mouse_t
	{
		Game::Circle circle;
		Game::coord2d coord;
	} static mouse;

	void Init(char* title, int width, int height, bool fullScreen);
	void setFullScreen(bool b);
	bool getFullScreen();
	void toggleFullScreen();
}