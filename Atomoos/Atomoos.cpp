#include "Game.h"
#include "Circle.h"
#include <gl/freeglut.h>
#include <iostream>
#include <vector>

int main(int argc, char **argv)
{
	Game::Init("beh", 900, 900, 0);

	glutMainLoop();
	
	return 0;
}

std::vector<Game::Circle*> circles;

void Game::mainRender()
{
	Game::write("cioa", { -0.9f, 0.9f }, {0.1f, 0.8f, 0.4f});
}