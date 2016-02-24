#include "Types.h"
#include <cmath>

coord2d::coord2d(GLfloat x, GLfloat y) : 
	x(x), y(y) 
{ }
coord2d::coord2d(GLint x, GLint y, int width, int height) : 
	x(x * 2 / (float)width - 1), 
	y(-y * 2 / (float)height + 1) 
{ }

GLfloat coord2d::getRadians() 
{
	float ang = atan2(y, x);
	if (ang < 0)
		ang += 2 * PI;
	return ang;
}

void coord2d::fromRadians(float radians, float radius = 1.0f)
{
	x = radius * cos(radians);
	y = radius * sin(radians);
}


float inline randf()
{
	return rand() / float(RAND_MAX);
}

colorRGB::colorRGB(GLfloat r, GLfloat g, GLfloat b) : 
	r(r), g(g), b(b) 
{ }

colorRGB* colorRGB::rand() 
{ 
	return new colorRGB(randf(), randf(), randf()); 
}