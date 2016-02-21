#include "Game.h"
#include "Circle.h"
#include "Types.h"
#include "Atom.h"
#include <gl/freeglut.h>
#include <iostream>
#include <vector>

std::vector<Atom*> atoms;

int main(int argc, char **argv)
{
	Game::Init("beh", 900, 900, 0);
	atoms.push_back(new Atom(new coord2d(0.6f, -0.5f), new colorRGB(1,1,1)));
	glutMainLoop();
	
	return 0;
}


void Game::mainRender()
{
	Game::write("cioa", { -0.9f, 0.9f }, {0.1f, 0.8f, 0.4f});
	atoms[0]->draw();
}