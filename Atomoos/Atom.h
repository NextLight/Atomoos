#pragma once
#include "Types.h"
#include "Circle.h"
class Atom : public Game::Circle 
{
public:
	Atom(coord2d* center, unsigned char number);

	unsigned char number;

	void draw();

	static std::pair<const char*, colorRGB> elements[];
	static void Init();

private:
	static const Game::Polygon* defaultPolygon;
};