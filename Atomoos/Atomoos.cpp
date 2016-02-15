#include <GL/glew.h>
#include <gl/freeglut.h>
#include <iostream>
#include "MooGL.h"

int main(int argc, char **argv)
{
	MooGL::Init("beh", 900, 900, 0, argc, argv);

	glutMainLoop();
	
	return 0;
}