#include "Circle.h"
#include "Types.h"
#include <cmath>
#include <iostream>
#include <memory>

Game::Circle::Circle(Game::Polygon* polygon, Game::coord2d* center, Game::colorRGB color) :
	polygon(polygon),
	center(center),
	color(color),
	shader(vertexSource, fragmentSource)
{
	shader.addUniformf("center", { &this->center->x, &this->center->y });
	shader.addUniformf("extColor", { &(this->color.r), &this->color.g, &this->color.b });
}

Game::Circle::Circle(GLsizei n, GLfloat r, Game::coord2d* center, Game::colorRGB color) :
	Circle(new Game::Polygon(generateVertices(n, r), n), center, color)
{ 
}

void Game::Circle::draw()
{
	shader.use({ "center" });
	polygon->draw();
}

GLfloat* Game::Circle::generateVertices(GLsizei n, GLfloat r)
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