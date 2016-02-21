#pragma once
#include <GL/glew.h>
//namespace Game
//{
	typedef struct coord2d {
		coord2d() {}
		coord2d(GLfloat x, GLfloat y) : x(x), y(y) {}
		GLfloat x, y;
	};

	typedef struct colorRGB {
		colorRGB(GLfloat r, GLfloat g, GLfloat b) : r(r), g(g), b(b) {}
		GLfloat r, g, b;
	};
//}