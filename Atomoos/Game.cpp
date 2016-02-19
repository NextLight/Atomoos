#include "Game.h"
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

void Game::Init(char* title, int width, int height, bool fullScreen)
{
	glutInit(new int, nullptr);
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

	mouse.circle = Circle(50, 0.25f, &mouse.coord, { 0.3f, 0.5f, 0.9f });
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Game::setFullScreen(bool b)
{
	if (b)
		glutFullScreen();
	else
		glutLeaveFullScreen();
}

bool Game::getFullScreen()
{
	return glutGet(GLUT_FULL_SCREEN);
}

void Game::toggleFullScreen()
{
	glutFullScreenToggle();
}

void reshape(int w, int h)
{
	Game::window.width = w;
	Game::window.height = h;
	int size = w < h ? w : h;
	glViewport(0, 0, w, h);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'f':
		Game::toggleFullScreen();
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
	Game::mouse.coord.x = +x * 2 / (float)Game::window.width - 1;
	Game::mouse.coord.y = -y * 2 / (float)Game::window.height + 1;
}

void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	Game::mouse.circle.draw();
	
	glutSwapBuffers();
}
