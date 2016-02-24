#pragma once
#include <GL/glew.h>

#define PI 3.14159265358979

struct coord2d {
	coord2d() {};
	coord2d(GLfloat x, GLfloat y);
	coord2d(GLint x, GLint y, int width, int height);

	GLfloat x, y;

	GLfloat getRadians();
	void fromRadians(float radians, float radius);
};

struct colorRGB {
	colorRGB(GLfloat r, GLfloat g, GLfloat b);
	GLfloat r, g, b;

	static colorRGB* rand();
};