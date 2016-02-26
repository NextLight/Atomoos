#include "Game.h"
#include "Circle.h"
#include "Types.h"
#include "Atom.h"
#include <gl/freeglut.h>
#include <string>
#include <iostream>
#include <vector>

#define max(a, b) a > b ? a : b

std::vector<Atom*> atoms;
Atom* centralAtom;
constexpr float circ = 2 * PI;
constexpr float radius = 0.7f;
int count = 0;
int lastRedPlus = 1;
int score = 0; // TODO

int main(int argc, char **argv)
{
	Game::Init("beh", 900, 900, 0);
	centralAtom = new Atom(new coord2d(0, 0), 1);
	glutMainLoop();
	return 0;
}

void Game::mainRender()
{
	centralAtom->draw();
	for (Atom* a : atoms)
		a->draw();
}

// return a random number in range [0, n)
int inline randrange(int n) {
	return rand() % n;
}

int reaction(int idx, bool forced = false) {
	int l = (idx == 0 ? atoms.size() : idx) - 1;
	int r = idx + 1 == atoms.size() ? 0 : idx + 1;
	if (atoms.size() > 2 && (atoms[l]->number == atoms[r]->number && atoms[l]->type == Atom::atype::normal || atoms[idx]->type == Atom::atype::black_plus)) {
		unsigned char number;
		if (atoms[idx]->type == Atom::atype::normal)
			number = atoms[idx]->number > atoms[l]->number ? atoms[idx]->number + 1 : atoms[l]->number + 2;
		else if (atoms[idx]->type == Atom::atype::red_plus)
			number = atoms[l]->number + 1;
		else // black_plus
			number = max(atoms[l]->number, atoms[r]->number) + 3;
		atoms[l] = new Atom(new coord2d(0, 0), number);
		atoms.erase(atoms.begin() + r);
		atoms.erase(atoms.begin() + idx - (r == 0));
		return 1 + reaction(l - (idx < l) - (r < l));
	}
	return 0;
}

// update atoms position based on atoms[idx] position
void updateAtomsPosition(int idx)
{
	float ang = atoms[idx]->center->getRadians(), theta = circ / atoms.size();
	for (int i = (idx + 1) % atoms.size(); i != idx; i = (i + 1) % atoms.size()) {
		ang += theta;
		atoms[i]->center->fromRadians(ang, radius);
	}
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

	atoms.insert(atoms.begin() + pos, centralAtom);
	float phase = atoms[0]->center->getRadians();
	ang = pos * theta - theta / 2 + phase;

	// change every atom postion accordingly
	atoms[pos]->center->fromRadians(ang, radius);
	updateAtomsPosition(pos);

	// look for chain reactions
	for (int i = 0; i < atoms.size(); i++)
		if (atoms[i]->type == Atom::atype::red_plus || atoms[i]->type == Atom::atype::black_plus) {
			if (int q = reaction(i)) {
				// if there's a reaction I have to update positions again and check for another one
				pos = (atoms.size() + i - q - (i >= atoms.size() + q ? atoms.size() + q - i + 1 : 0)) % atoms.size();
				ang = i * theta - theta / 2 + phase;
				atoms[pos]->center->fromRadians(ang, radius);
				updateAtomsPosition(pos);
				theta = circ / atoms.size();
				phase = atoms[0]->center->getRadians();
				i = -1; // beware of teh bad wolf
			}
		}

	// Calulate energy particles spawning chance.
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