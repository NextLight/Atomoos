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
int count = 0;
int lastRedPlus = 1;
int score = 0;

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

// n is exclusive
int inline randrange(int n) {
	return rand() % n;
}

void Game::mouseLeftDown(coord2d c)
{
	++count;
	// calculate inserted atom position in vector
	int pos = 0;
	float theta = 0, ang = c.getRadians();
	if (atoms.size() > 0) {
		theta = circ / atoms.size();
		float start = atoms[0]->center->getRadians();
		if (start > ang)
			start -= circ;
		pos = floor((ang - start) / theta) + 1;
	}
	s = std::to_string(c.x) + " " + std::to_string(c.y) + " : " + std::to_string(ang);

	atoms.insert(atoms.begin() + pos, centralAtom);

	// change every atom postion accordingly
	ang = pos * theta - theta / 2 + atoms[0]->center->getRadians();
	atoms[pos]->center->fromRadians(ang, radius);
	theta = circ / atoms.size();
	for (int i = (pos + 1) % atoms.size(); i != pos; i = (i + 1) % atoms.size()) {
		ang += theta;
		atoms[i]->center->fromRadians(ang, radius);
	}

	// Calulate atomasses spawning chance.
	Atom::atype type = Atom::atype::normal;
	// Every time the red plus isn't picked up its chance is doubled and the 5th time (32) is 100%.
	// I think this works quite well but I should RE the game (or ask the dev eh) to know the real algorithm.
	lastRedPlus *= 2;
	if (count % 20 == 0) {
		type = Atom::atype::minus;
	}
	else if (randrange(32) < lastRedPlus) {
		type = Atom::atype::red_plus;
		lastRedPlus = 1;
	}
	else if (score > 750 && randrange(80) == 0) {
		type = Atom::atype::black_plus;
	}
	else if (score > 1500 && randrange(60) == 0) {
		type = Atom::atype::neutrino;
	}

	unsigned char number = 0, startRange = 1 + count / 40;
	if (type == Atom::atype::normal) {
		number = startRange + randrange(4);
		// check if there's an atom below the spawning range
		for (Atom* a : atoms) if (a->type == Atom::atype::normal && a->number < startRange)
			if (randrange(atoms.size() - 1) == 0) {
				number = a->number;
				break;
			}
	}
	centralAtom = new Atom(new coord2d(0, 0), type, number);
}