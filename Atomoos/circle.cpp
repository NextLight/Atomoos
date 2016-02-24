#include "Circle.h"
#include "Types.h"
#include <cmath>
#include <iostream>
#include <memory>

Game::Circle::Circle(const Game::Polygon* polygon, coord2d* center, colorRGB* color) :
	polygon(polygon),
	center(center),
	color(color),
	shader(vertexSource, fragmentSource)
{
	shader.addUniformf("center", { &center->x, &center->y });
	shader.addUniformf("extColor", { &color->r, &color->g, &color->b });
}

Game::Circle::Circle(GLsizei n, GLfloat r, coord2d* center, colorRGB* color) :
	Circle(new Game::Polygon(generateVertices(n, r), n), center, color)
{ 
}

void Game::Circle::draw()
{
	shader.use({ "center" });
	polygon->draw();
}

const GLfloat* Game::Circle::generateVertices(GLsizei n, GLfloat r)
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