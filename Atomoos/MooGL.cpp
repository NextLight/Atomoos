#include "MooGL.h"
#include <GL/freeglut.h>
#include <GL/glew.h>
#include <cstdio>
#include <iostream>
#include <cmath>

#include "circle.h"

void render(void);
void mouseClick(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void reshape(int w, int h);
void updateMousePosition(int x, int y);

void MooGL::Init(char* title, int width, int height, bool fullScreen, int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(window.width = width, window.height = height);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow(title);
	setFullScreen(fullScreen);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glutDisplayFunc(render);
	glutIdleFunc(render);
	glutMouseFunc(mouseClick);
	glutPassiveMotionFunc(updateMousePosition);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	glewExperimental = GL_TRUE;
	glewInit();

	mouse.circle = circle(50, 0.25f, &mouse.coord, { 1.0f, 0.5f, 0.2f });
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
/*
void MooGL::Close()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
*/

void MooGL::setFullScreen(bool b)
{
	if (b)
		glutFullScreen();
	else
		glutLeaveFullScreen();
}

bool MooGL::getFullScreen()
{
	return glutGet(GLUT_FULL_SCREEN);
}

void MooGL::toggleFullScreen()
{
	glutFullScreenToggle();
}

GLuint MooGL::compileShader(const GLchar* source, shaderType type)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	GLint success;
	GLchar log[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, log);
		std::cout << "ERROR SHADER COMPILATION FAILED\n" << log << std::endl;
		return 0; // ?
	}
	return shader;
}

GLuint MooGL::programShader(GLchar* vertex, GLchar* fragment)
{
	GLuint vertexShader = compileShader(vertex, shaderType::vertex);
	GLuint fragmentShader = compileShader(fragment, shaderType::fragment);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	GLint success;
	GLchar log[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, log);
		std::cout << "ERROR SHADER LINKING FAILED\n" << log << std::endl;
		return 0; // ?
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderProgram;
}

void reshape(int w, int h)
{
	MooGL::window.width = w;
	MooGL::window.height = h;
	int size = w < h ? w : h;
	//glViewport((w - size) / 2, (h - size) / 2, size, size);
	glViewport(0, 0, w, h);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'f':
		MooGL::toggleFullScreen();
		break;
	case 27: // ESC
		exit(0);
	}
}

void mouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
		// TODO
		return;
}

void updateMousePosition(int x, int y)
{
	MooGL::mouse.coord.x = +x * 2 / (float)MooGL::window.width - 1;
	MooGL::mouse.coord.y = -y * 2 / (float)MooGL::window.height + 1;
}

void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	MooGL::mouse.circle.draw();
	
	glutSwapBuffers();
}
