#pragma once
#include "Types.h"
#include "Circle.h"
class Atom : public Game::Circle 
{
public:
	enum atype {
		normal, red_plus, black_plus, minus, neutrino
	} type;

	Atom(coord2d* center, Atom::atype type, unsigned char number);
	Atom(coord2d* center, unsigned char number);

	const unsigned char number;

	void draw();

	struct element {
		const char* symbol;
		colorRGB color;
		const char* name;
	} static elements[], atomasses[];

	static void Init();

private:
	static const Game::Polygon* defaultPolygon;
};