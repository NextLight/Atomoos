#include "Atom.h"
#include "Polygon.h"

const Game::Polygon* Atom::defaultPolygon = nullptr;

Atom::Atom(coord2d* center, colorRGB* color) : 
	Circle(defaultPolygon, center, color)
{
}

void Atom::Init()
{
	Atom::defaultPolygon = new Game::Polygon(Circle::generateVertices(200, 0.1), 200);
}
