#include "circle.h"
#include "mooTypes.h"
#include "MooGL.h"
#include <cmath>
#include <iostream>

MooGL::circle::circle(MooGL::polygon polygon, MooGL::coord2d* center, MooGL::colorRGB color) :
	polygon(polygon),
	center(center),
	color(color)
{
	shaderProgram = MooGL::programShader(vertexSource, fragmentSource);
	uniformCenter = glGetUniformLocation(shaderProgram, "center");
	uniformColor = glGetUniformLocation(shaderProgram, "extColor");
}

MooGL::circle::circle(GLsizei n, GLfloat r, MooGL::coord2d* center, MooGL::colorRGB color) :
	circle(MooGL::polygon(generateVertices(n, r), n), center, color)
{ 
}

MooGL::circle::~circle()
{
}

void MooGL::circle::draw()
{
	glUseProgram(shaderProgram);
	glUniform2f(uniformCenter, center->x, center->y);
	glUniform3f(uniformColor, color.r, color.g, color.b);
	glBindVertexArray(polygon.VAO);
	glDrawArrays(GL_POLYGON, 0, polygon.size);
	glBindVertexArray(0);
}

GLfloat* MooGL::circle::generateVertices(GLsizei n, GLfloat r)
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