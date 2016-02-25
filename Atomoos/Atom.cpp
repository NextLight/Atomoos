#include "Atom.h"
#include "Polygon.h"
#include "Game.h"

const Game::Polygon* Atom::defaultPolygon = nullptr;

Atom::Atom(coord2d* center, Atom::atype type, const unsigned char number = 0) : 
	Circle(defaultPolygon, center, &(type == atype::normal ? elements[number] : atomasses[type]).color),
	type(type),
	number(number)
{
}

Atom::Atom(coord2d * center, const unsigned char number) :
	Atom(center, atype::normal, number)
{
}

void Atom::draw()
{
	Circle::draw();

	const char* text = (type == atype::normal ? elements[number] : atomasses[type]).symbol;
	Game::write(text, { center->x - Game::getTextWidth(text) / 2, center->y - Game::getFontHeight() / 2 }, { 1, 1, 1 });
}

void Atom::Init()
{
	Atom::defaultPolygon = new Game::Polygon(Circle::generateVertices(200, 0.1), 200);
}

Atom::element Atom::atomasses[] = {
	{ " ", { 1, 1, 1 } },
	{ "+", { 1, 0, 0 } },
	{ "+", { 0, 0, 0 } },
	{ "-", { 0, 0, 1 } },
	{ " ", { 1, 1, 1 } }
};

Atom::element Atom::elements[] = {
	{ "",	{ 1.000000f, 1.000000f,	1.000000f }, "" },
	{ "H",	{ 0.388235f, 0.725490f, 0.835294f }, "Hydrogen" },
	{ "He",	{ 0.819608f, 0.788235f, 0.568627f }, "Helium" },
	{ "Li",	{ 0.298039f, 0.380392f, 0.407843f }, "Lithium" },
	{ "Be",	{ 0.784314f, 0.784314f, 0.784314f }, "Beryllium" },
	{ "B",	{ 0.490196f, 0.325490f, 0.325490f }, "Boron" },
	{ "C",	{ 0.231373f, 0.231373f, 0.231373f }, "Carbon" },
	{ "N",	{ 0.172549f, 0.776471f, 0.698039f }, "Nitrogen" },
	{ "O",	{ 0.435294f, 0.925490f, 0.596078f }, "Oxygen" },
	{ "F",	{ 0.925490f, 0.768627f, 0.435294f }, "Fluorine" },
	{ "Ne",	{ 0.745098f, 0.000000f, 0.525490f }, "Neon" },
	{ "Na",	{ 0.901961f, 0.615686f, 0.478431f }, "Sodium" },
	{ "Mg",	{ 0.619608f, 0.501961f, 0.917647f }, "Magnesium" },
	{ "Al",	{ 0.474510f, 0.474510f, 0.474510f }, "Aluminum" },
	{ "Si",	{ 0.290196f, 0.250980f, 0.439216f }, "Silicon" },
	{ "P",	{ 0.843137f, 0.274510f, 0.247059f }, "Phosphorus" },
	{ "S",	{ 0.215686f, 0.368627f, 0.486275f }, "Sulfur" },
	{ "Cl",	{ 0.427451f, 0.113725f, 0.482353f }, "Chlorine" },
	{ "Ar",	{ 0.603922f, 0.239216f, 0.647059f }, "Argon" },
	{ "K",	{ 0.301961f, 0.537255f, 0.274510f }, "Potassium" },
	{ "Ca",	{ 0.941176f, 0.941176f, 0.941176f }, "Calcium" },
	{ "Sc",	{ 0.372549f, 0.733333f, 0.466667f }, "Scandium" },
	{ "Ti",	{ 0.352941f, 0.352941f, 0.352941f }, "Titanium" },
	{ "V",	{ 0.372549f, 0.619608f, 0.733333f }, "Vanadium" },
	{ "Cr",	{ 0.643137f, 0.533333f, 0.709804f }, "Chromium" },
	{ "Mn",	{ 0.862745f, 0.290196f, 0.290196f }, "Manganese" },
	{ "Fe",	{ 0.670588f, 0.588235f, 0.490196f }, "Iron" },
	{ "Co",	{ 0.262745f, 0.443137f, 0.901961f }, "Cobalt" },
	{ "Ni",	{ 0.729412f, 0.764706f, 0.584314f }, "Nickel" },
	{ "Cu",	{ 0.725490f, 0.341176f, 0.223529f }, "Copper" },
	{ "Zn",	{ 0.705882f, 0.705882f, 0.705882f }, "Zinc" },
	{ "Ga",	{ 0.223529f, 0.725490f, 0.458824f }, "Gallium" },
	{ "Ge",	{ 0.592157f, 0.572549f, 0.450980f }, "Germanium" },
	{ "As",	{ 0.450980f, 0.517647f, 0.596078f }, "Arsenic" },
	{ "Se",	{ 0.258824f, 0.258824f, 0.258824f }, "Selenium" },
	{ "Br",	{ 0.831373f, 0.458824f, 0.235294f }, "Bromine" },
	{ "Kr",	{ 0.235294f, 0.627451f, 0.831373f }, "Krypton" },
	{ "Rb",	{ 0.823529f, 0.172549f, 0.121569f }, "Rubidium" },
	{ "Sr",	{ 1.000000f, 0.615686f, 0.160784f }, "Strontium" },
	{ "Y",	{ 0.694118f, 0.160784f, 1.000000f }, "Yttrium" },
	{ "Zr",	{ 0.839216f, 0.894118f, 0.243137f }, "Zirconium" },
	{ "Nb",	{ 0.458824f, 0.862745f, 0.921569f }, "Niobium" },
	{ "Mo",	{ 0.545098f, 0.639216f, 0.549020f }, "Molybdenum" },
	{ "Tc",	{ 0.933333f, 0.631373f, 0.886275f }, "Technetium" },
	{ "Ru",	{ 0.337255f, 0.243137f, 0.196078f }, "Ruthenium" },
	{ "Rh",	{ 0.533333f, 0.819608f, 0.478431f }, "Rhodium" },
	{ "Pd",	{ 0.619608f, 0.670588f, 0.745098f }, "Palladium" },
	{ "Ag",	{ 0.862745f, 0.862745f, 0.862745f }, "Silver" },
	{ "Cd",	{ 0.333333f, 0.376471f, 0.784314f }, "Cadmium" },
	{ "In",	{ 0.250980f, 0.552941f, 0.235294f }, "Indium" },
	{ "Sn",	{ 0.709804f, 0.643137f, 0.486275f }, "Tin" },
	{ "Sb",	{ 0.776471f, 0.349020f, 0.549020f }, "Antimony" },
	{ "Te",	{ 0.509804f, 0.454902f, 0.596078f }, "Tellurium" },
	{ "I",	{ 1.000000f, 0.000000f, 0.988235f }, "Iodine" },
	{ "Xe",	{ 0.470588f, 0.533333f, 1.000000f }, "Xenon" },
	{ "Cs",	{ 1.000000f, 0.831373f, 0.470588f }, "Cae­sium" },
	{ "Ba",	{ 0.913725f, 0.611765f, 0.611765f }, "Barium" },
	{ "La",	{ 0.545098f, 0.858824f, 0.745098f }, "Lanthanum" },
	{ "Ce",	{ 1.000000f, 0.576471f, 0.160784f }, "Cerium" },
	{ "Pr",	{ 0.337255f, 0.878431f, 0.098039f }, "Praseodymium" },
	{ "Nd",	{ 0.396078f, 0.537255f, 0.552941f }, "Neodymium" },
	{ "Pm",	{ 0.180392f, 0.913725f, 0.607843f }, "Promethium" },
	{ "Sm",	{ 0.741176f, 0.392157f, 0.458824f }, "Samarium" },
	{ "Eu",	{ 0.423529f, 0.392157f, 0.741176f }, "Europium" },
	{ "Gd",	{ 0.431373f, 0.070588f, 0.537255f }, "Gadolinium" },
	{ "Tb",	{ 0.207843f, 0.611765f, 0.313725f }, "Terbium" },
	{ "Dy",	{ 0.266667f, 0.494118f, 0.905882f }, "Dysprosium" },
	{ "Ho",	{ 0.905882f, 0.490196f, 0.274510f }, "Holmium" },
	{ "Er",	{ 0.749020f, 0.286275f, 0.529412f }, "Erbium" },
	{ "Tm",	{ 0.129412f, 0.258824f, 0.419608f }, "Thulium" },
	{ "Yb",	{ 0.529412f, 0.529412f, 0.313725f }, "Ytterbium" },
	{ "Lu",	{ 0.819608f, 0.172549f, 0.172549f }, "Lutetium" },
	{ "Hf",	{ 0.568627f, 0.819608f, 0.172549f }, "Hafnium" },
	{ "Ta",	{ 0.498039f, 0.529412f, 0.686275f }, "Tantalum" },
	{ "W",	{ 0.168627f, 0.415686f, 0.647059f }, "Tungsten" },
	{ "Re",	{ 0.317647f, 0.184314f, 0.184314f }, "Rhenium" },
	{ "Os",	{ 0.188235f, 0.439216f, 0.376471f }, "Osmium" },
	{ "Ir",	{ 0.788235f, 0.529412f, 0.415686f }, "Iridium" },
	{ "Pt",	{ 0.313725f, 0.313725f, 0.031373f }, "Platinum" },
	{ "Au",	{ 0.929412f, 0.768627f, 0.454902f }, "Gold" },
	{ "Hg",	{ 0.501961f, 0.647059f, 0.674510f }, "Mercury" },
	{ "Tl",	{ 0.674510f, 0.501961f, 0.537255f }, "Thallium" },
	{ "Pb",	{ 0.235294f, 0.486275f, 0.400000f }, "Lead" },
	{ "Bi",	{ 1.000000f, 0.019608f, 0.023529f }, "Bismuth" },
	{ "Po",	{ 1.000000f, 1.000000f, 0.000000f }, "Polonium" },
	{ "At",	{ 0.000000f, 1.000000f, 0.000000f }, "Astatine" },
	{ "Rn",	{ 0.854902f, 0.909804f, 0.227451f }, "Radon" },
	{ "Fr",	{ 1.000000f, 0.423529f, 0.000000f }, "Francium" },
	{ "Ra",	{ 0.000000f, 1.000000f, 1.000000f }, "Radium" },
	{ "Ac",	{ 0.258824f, 0.286275f, 0.094118f }, "Actinium" },
	{ "Th",	{ 0.666667f, 0.239216f, 0.509804f }, "Thorium" },
	{ "Pa",	{ 0.239216f, 0.666667f, 0.509804f }, "Protactinium" },
	{ "U",	{ 0.611765f, 1.000000f, 0.000000f }, "Uranium" },
	{ "Np",	{ 0.000000f, 0.682353f, 1.000000f }, "Neptunium" },
	{ "Pu",	{ 1.000000f, 0.564706f, 0.000000f }, "Plutonium" },
	{ "Am",	{ 0.505882f, 0.200000f, 0.286275f }, "Americium" },
	{ "Cm",	{ 1.000000f, 0.474510f, 0.815686f }, "Curium" },
	{ "Bk",	{ 0.682353f, 0.529412f, 0.494118f }, "Berkelium" },
	{ "Cf",	{ 0.560784f, 0.235294f, 0.705882f }, "Californium" },
	{ "Es",	{ 0.525490f, 0.768627f, 0.862745f }, "Einsteinium" },
	{ "Fm",	{ 0.749020f, 0.862745f, 0.525490f }, "Fermium" },
	{ "Md",	{ 0.862745f, 0.525490f, 0.525490f }, "Mendelevium" },
	{ "No",	{ 1.000000f, 0.850980f, 0.396078f }, "Nobelium" },
	{ "Lr",	{ 0.360784f, 0.141176f, 0.627451f }, "Lawrencium" },
	{ "Rf",	{ 0.419608f, 0.400000f, 0.458824f }, "Rutherfordium" },
	{ "Db",	{ 0.690196f, 0.313725f, 0.196078f }, "Dubnium" },
	{ "Sg",	{ 0.145098f, 0.286275f, 0.529412f }, "Seaborgium" },
	{ "Bh",	{ 0.607843f, 0.686275f, 0.627451f }, "Bohrium" },
	{ "Hs",	{ 1.000000f, 0.337255f, 0.176471f }, "Hassium" },
	{ "Mt",	{ 0.803922f, 0.803922f, 0.172549f }, "Meitnerium" },
	{ "Ds",	{ 0.227451f, 0.494118f, 0.282353f }, "Darmstadtium" },
	{ "Rg",	{ 0.109804f, 0.450980f, 0.921569f }, "Roentgenium" },
	{ "Cn",	{ 0.666667f, 0.270588f, 0.580392f }, "Copernicium" },
	{ "Uut",{ 0.560784f, 0.560784f, 0.560784f }, "Ununtrium" },
	{ "Fl",	{ 0.180392f, 0.929412f, 0.901961f }, "Flerovium" },
	{ "Uup",{ 0.745098f, 0.686275f, 0.392157f }, "Ununpentium" },
	{ "Lv",	{ 0.949020f, 0.180392f, 0.415686f }, "Livermorium" },
	{ "Uus",{ 0.439216f, 0.917647f, 0.470588f }, "Ununseptium" },
	{ "Uuo",{ 1.000000f, 0.000000f, 0.725490f }, "Ununoctium" },
	{ "Bn",	{ 0.929412f, 0.901961f, 0.454902f }, "Bananium" },
	{ "Gb",	{ 0.239216f, 0.901961f, 0.764706f }, "GravityBlockium" },
	{ "Bb",	{ 0.188235f, 0.568627f, 0.254902f }, "BreakingBadium" },
	{ "Tr",	{ 0.301961f, 0.784314f, 0.901961f }, "TimeRunnerium" },
	{ "Sir",{ 1.000000f, 0.000000f, 0.000000f }, "Sirnicanium" },
	{ "Unk",{ 0.000000f, 0.000000f, 0.000000f }, "Unknown" }
};