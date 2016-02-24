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
constexpr float circ = 2 * PI;
constexpr float radius = 0.7f;

int main(int argc, char **argv)
{
	Game::Init("beh", 900, 900, 0);
	centralAtom = new Atom(new coord2d(0, 0), 1);
	glutMainLoop();
	return 0;
}

std::string s = "a";
void Game::mainRender()
{
	Game::write(s.c_str(), { -0.95f, 0.95f }, { 0.1f, 0.8f, 0.4f });
	centralAtom->draw();
	for (Atom* a : atoms)
		a->draw();
}

// min is inclusive, max is exclusive.
int randrange(int min, int max) {
	return min + rand() % (max - min);
}

void Game::mouseLeftDown(coord2d c)
{
	int pos = 0;
	float theta = 0, ang = c.getRadians();
	if (atoms.size() > 0) {
		theta = circ / atoms.size();
		float start = atoms[0]->center->getRadians();
		if (start > ang)
			start -= circ;
		pos = floor((ang - start) / theta) + 1;
	}
	atoms.insert(atoms.begin() + pos, centralAtom);
	s = std::to_string(c.x) + " " + std::to_string(c.y) + " : " + std::to_string(ang);
	
	ang = pos * theta - theta / 2 + atoms[0]->center->getRadians();
	atoms[pos]->center->fromRadians(ang, radius);
	theta = circ / atoms.size();
	for (int i = (pos + 1) % atoms.size(); i != pos; i = (i + 1) % atoms.size()) {
		ang += theta;
		atoms[i]->center->fromRadians(ang, radius);
	}
	centralAtom = new Atom(new coord2d(0, 0), randrange(1, 5));
}