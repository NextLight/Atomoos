#pragma once
#include <GL/glew.h>
typedef struct coord2d {
	coord2d() {}
	coord2d(GLfloat x, GLfloat y) : x(x), y(y) {}
	coord2d(GLint x, GLint y, int width, int height) : x(x * 2 / (float)width - 1), y(-y * 2 / (float)height + 1) {}

	GLfloat x, y;
};

typedef struct colorRGB {
	colorRGB(GLfloat r, GLfloat g, GLfloat b) : r(r), g(g), b(b) {}
	GLfloat r, g, b;
};