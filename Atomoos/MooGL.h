#pragma once
#include "mooTypes.h"
#include "polygon.h"
#include "circle.h"
//#include "mouse.h"
namespace MooGL
{
	struct window_t {
		int width, height;
	} static window;

	struct mouse_t
	{
		MooGL::Circle circle;
		MooGL::coord2d coord;
	} static mouse;

	void Init(char* title, int width, int height, bool fullScreen,int argc, char **argv);
	void setFullScreen(bool b);
	bool getFullScreen();
	void toggleFullScreen();
}