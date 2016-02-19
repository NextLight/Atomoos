#pragma once
#include <GL/glew.h>
namespace Game
{
	class Polygon
	{
	public:
		Polygon() {}
		Polygon(GLfloat* vertices, GLsizei size);
		~Polygon();
		GLuint VAO;
		GLsizei size;

		void draw() const;
	private:
		GLuint VBO;
	};
}