#pragma once
#include <GL/glew.h>
namespace MooGL
{
	class polygon
	{
	public:
		polygon() {}
		polygon(GLfloat* vertices, GLsizei size);
		GLuint VAO;
		GLsizei size;
	};
}