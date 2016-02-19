#include "Game.h"
#include <GL/glew.h>
#include <gl/freeglut.h>
#include <iostream>

int main(int argc, char **argv)
{
	Game::Init("beh", 900, 900, 0, argc, argv);

	glutMainLoop();
	
	return 0;
}