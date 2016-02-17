#include "circle.h"
#include "mooTypes.h"
#include "MooGL.h"
#include <cmath>
#include <iostream>
#include <memory>

MooGL::Circle::Circle(MooGL::Polygon polygon, MooGL::coord2d* center, MooGL::colorRGB color) :
	polygon(polygon),
	center(center),
	color(color),
	shader(vertexSource, fragmentSource)
{
	shader.addUniformf("center", { &this->center->x, &this->center->y });
	shader.addUniformf("extColor", { &(this->color.r), &this->color.g, &this->color.b });
}

MooGL::Circle::Circle(GLsizei n, GLfloat r, MooGL::coord2d* center, MooGL::colorRGB color) :
	Circle(MooGL::Polygon(generateVertices(n, r), n), center, color)
{ 
}

void MooGL::Circle::draw()
{
	shader.use({ "center" });
	polygon.draw();
}

GLfloat* MooGL::Circle::generateVertices(GLsizei n, GLfloat r)
{
	int size = n * 2;
	GLfloat* res = new GLfloat[size];
	float theta = 2 * PI / float(n), ang = 0;
	for (int i = 0; i < size; i += 2) {
		res[i] = sinf(ang) * r;
		res[i + 1] = cosf(ang) * r;
		ang += theta;
	}
	return res;
}