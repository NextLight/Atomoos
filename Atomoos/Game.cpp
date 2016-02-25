#include "Game.h"
#include <GL/freeglut.h>
#include <GL/glew.h>
#include "Types.h"
#include <cstdio>
#include <iostream>
#include <cmath>
#include <string>
#include <ctime>
#include "Circle.h"
#include "Atom.h"

void render(void);
void mouseClick(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);
void reshape(int w, int h);
void updateMousePosition(int x, int y);

namespace Game
{
	window_t window;
	mouse_t mouse;

	void Init(char* title, int width, int height, bool fullScreen)
	{
		srand(time(NULL));
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

		Atom::Init();
		mouse.circle = Circle(50, 0.025f, &mouse.coord, new colorRGB(0.3f, 0.5f, 0.9f));
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void setFullScreen(bool b)
	{
		if (b)
			glutFullScreen();
		else
			glutLeaveFullScreen();
	}

	bool getFullScreen()
	{
		return glutGet(GLUT_FULL_SCREEN);
	}

	void toggleFullScreen()
	{
		glutFullScreenToggle();
	}

	void write(const char* s, coord2d* coord, colorRGB color, fontType font, bool center)
	{
		//glLoadIdentity();
		//glScalef(0.3, 0.3, 1);
		glColor3f(color.r, color.g, color.b);
		coord2d* pos = center ? getTextCenter(s, coord, font) : coord;
		glRasterPos2f(pos->x, pos->y);
		glutBitmapString((void*)font, (const unsigned char*)s);
		// TODO: use glutStrokeString(GLUT_STROKE_ROMAN, (const unsigned char*)s);
	}

	GLfloat getTextWidth(const char* s, fontType font) 
	{
		return glutBitmapLength((void*)font, (const unsigned char*)s) * 2 / (GLfloat)window.width;
	}

	GLfloat getFontHeight(fontType font) 
	{
		// Upper case chars are ~15/23 the height returned by glutBitmapHeight.
		return (glutBitmapHeight((void*)font) * 2 / (GLfloat)window.height) * 15 / 23;
	}

	coord2d* getTextCenter(const char* s, coord2d* coord, fontType font) 
	{
		return new coord2d(coord->x - Game::getTextWidth(s, font) / 2, coord->y - Game::getFontHeight(font) / 2);
	}
}

void reshape(int w, int h)
{
	Game::window.width = w;
	Game::window.height = h;
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
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		Game::mouseLeftDown(coord2d(x, y, Game::window.width, Game::window.height));
}

void updateMousePosition(int x, int y)
{
	Game::mouse.coord = coord2d(x, y, Game::window.width, Game::window.height);
}

void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Game::mouse.circle.draw();
	Game::mainRender();
	
	glutSwapBuffers();
}
