#include "Polygon.h"

Game::Polygon::Polygon(GLfloat* vertices, GLsizei size) :
	size(size)
{
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size * 2 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Game::Polygon::~Polygon()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}

void Game::Polygon::draw() const
{
	glBindVertexArray(VAO);
	glDrawArrays(GL_POLYGON, 0, size);
	glBindVertexArray(0);
}