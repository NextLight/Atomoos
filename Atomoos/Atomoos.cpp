#include "Game.h"
#include "Circle.h"
#include "Types.h"
#include "Atom.h"
#include <gl/freeglut.h>
#include <string>
#include <iostream>
#include <vector>

std::vector<Atom*> atoms;
Atom* centralAtom;
std::string s = "a";
constexpr float circ = 2 * PI;
constexpr float radius = 0.7f;

int main(int argc, char **argv)
{
	Game::Init("beh", 900, 900, 0);
	centralAtom = new Atom(new coord2d(0, 0), colorRGB::rand());
	glutMainLoop();
	return 0;
}


void Game::mainRender()
{
	Game::write(s.c_str(), { -0.9f, 0.9f }, { 0.1f, 0.8f, 0.4f });
	centralAtom->draw();
	for (Atom* a : atoms)
		a->draw();
}

void Game::mouseLeftDown(coord2d c)
{
	// this misteriously prints 0 0  
	//std::cout << Game::window.width << " " << Game::window.height << std::endl;
	int pos = 0;
	float theta, ang = 0;
	if (atoms.size() > 0) {
		theta = circ / atoms.size();
		ang = atan2(c.y, c.x);
		if (ang < 0)
			ang += circ;
		pos = floor(ang / theta) + 1;
	}
	atoms.insert(atoms.begin() + pos, centralAtom);
	s = std::to_string(c.x) + " " + std::to_string(c.y) + " : " + std::to_string(ang);
	
	theta = circ / atoms.size();
	ang = 0;
	for (Atom* a : atoms) {
		a->center->x = radius * cos(ang);
		a->center->y = radius * sin(ang);
		ang += theta;
	}
	centralAtom = new Atom(new coord2d(0, 0), colorRGB::rand());
}