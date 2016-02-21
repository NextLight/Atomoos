#pragma once
#include "Types.h"
#include "Circle.h"
class Atom : public Game::Circle {
public:
	Atom(coord2d* center, colorRGB* color);

	unsigned char value;

	static void Init();
private:
	static const Game::Polygon* defaultPolygon;
};