#include "Game.h"
#include "Circle.h"
#include "Types.h"
#include "Atom.h"
#include <gl/freeglut.h>
#include <string>
#include <iostream>
#include <vector>

std::vector<Atom*> atoms;

int main(int argc, char **argv)
{
	Game::Init("beh", 900, 900, 0);
	
	glutMainLoop();
	return 0;
}

std::string s = "a";

void Game::mainRender()
{
	Game::write(s.c_str(), { -0.9f, 0.9f }, {0.1f, 0.8f, 0.4f});
	for (Atom* a : atoms)
		a->draw();
}

void Game::mouseLeftDown(coord2d c)
{
	// this misteriously prints 0 0  
	std::cout << Game::window.width << " " << Game::window.height << std::endl;
	s = std::to_string(c.x) + " " + std::to_string(c.y);
	atoms.push_back(new Atom(new coord2d(c), new colorRGB(1, 1, 1)));
}