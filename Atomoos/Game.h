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

	 enum fontType {
		 helvetica10 = 6, helvetica12, helvetica18
	 };

	void Init(char * title, int width, int height, bool fullScreen);
	void setFullScreen(bool b);
	bool getFullScreen();
	void toggleFullScreen();

	void mainRender();
	void mouseLeftDown(coord2d c);

	void write(const char * s, coord2d* coord, colorRGB color, fontType font, bool center = true);

	GLfloat getTextWidth(const char * s, fontType font);

	GLfloat getFontHeight(fontType font);

	coord2d * getTextCenter(const char * s, coord2d * coord, fontType font);

	extern window_t window;
	extern mouse_t mouse;
}