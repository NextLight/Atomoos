#include "shaderProgram.h"

#include <iostream>

#include "gl/glew.h"

GLuint ShaderProgram::currentProgram = 0;

ShaderProgram::ShaderProgram(const GLchar* vertexSource, const GLchar* fragmentSource)
{
	GLuint vertexShader = compile(vertexSource, shaderType::vertex);
	GLuint fragmentShader = compile(fragmentSource, shaderType::fragment);
	program = link(vertexShader, fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void inline ShaderProgram::use()
{
	if (ShaderProgram::currentProgram != program) {
		glUseProgram(program);
		ShaderProgram::currentProgram = program;
	}
}

void ShaderProgram::use(const std::initializer_list<std::string> v)
{
	use();
	for (const std::string& u : v)
		updateUniform(uniformsf[u]);
}

GLuint inline ShaderProgram::getProgram() const
{
	return program;
}


void ShaderProgram::addUniformf(const std::string& name, const std::initializer_list<GLfloat*> v)
{
	auto a = new GLfloat*[v.size()];
	int i = 0;
	for (GLfloat* f : v)
		a[i++] = f;
	uniformsf[name] = { glGetUniformLocation(program, name.c_str()), a, v.size() };
	glUseProgram(program);
	updateUniform(uniformsf[name]);
}

void ShaderProgram::updateUniform(uniform_t u)
{
	switch (u.size)
	{
	case 1:
		glUniform1f(u.id, *u.v[0]);
		break;
	case 2:
		glUniform2f(u.id, *u.v[0], *u.v[1]);
		break;
	case 3:
		glUniform3f(u.id, *u.v[0], *u.v[1], *u.v[2]);
		break;
	case 4:
		glUniform4f(u.id, *u.v[0], *u.v[1], *u.v[2], *u.v[3]);
		break;
	default:
		std::cout << "Error. Array size is: " + u.size << std::endl;
		break;
	}
}

GLuint ShaderProgram::compile(const GLchar* source, shaderType type)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, log);
		std::cout << "ERROR SHADER COMPILATION FAILED:\n" << log << std::endl;
		return 0; // ?
	}
	return shader;
}

GLuint ShaderProgram::link(GLuint vertex, GLuint fragment)
{
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertex);
	glAttachShader(shaderProgram, fragment);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, log);
		std::cout << "ERROR SHADER LINKING FAILED:\n" << log << std::endl;
		return 0; // ?
	}
	return shaderProgram;
}
