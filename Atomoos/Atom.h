#pragma once
#include "Types.h"
#include "Circle.h"
class Atom : public Game::Circle 
{
public:
	Atom(coord2d* center, unsigned char number);

	unsigned char number;

	void draw();

	struct element {
		const char* symbol;
		colorRGB color;
		const char* name;
	} static elements[];

	static void Init();

private:
	static const Game::Polygon* defaultPolygon;
};