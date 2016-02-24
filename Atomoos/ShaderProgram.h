#pragma once
#include "gl/glew.h"
#include <unordered_map>

struct uniform_t {
	GLint id;
	GLfloat** v;
	size_t size;
};

class ShaderProgram
{
public:
	ShaderProgram() {}
	ShaderProgram(const GLchar * vertex, const GLchar * fragment);

	void use();
	void use(const std::initializer_list<std::string> v);
	
	enum shaderType : GLenum { vertex = GL_VERTEX_SHADER, fragment = GL_FRAGMENT_SHADER };

	GLuint getProgram() const;

	void addUniformf(const std::string & name, std::initializer_list<GLfloat*> v);

	void updateUniform(uniform_t u);

	static GLuint currentProgram;

private:
	GLint success;
	GLchar log[512];
	GLuint program;
	std::unordered_map<std::string, uniform_t> uniformsf;

	GLuint compile(const GLchar * source, shaderType type);

	GLuint link(GLuint vertex, GLuint fragment);

};

