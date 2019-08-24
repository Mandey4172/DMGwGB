#include "Neighborhood.h"

Neighborhood::Neighborhood()
{
	radius = 1;
}

Neighborhood::Neighborhood(const Neighborhood & o)
{
}

Neighborhood::~Neighborhood()
{
}

std::vector<unsigned int> Neighborhood::get(const std::shared_ptr<CellularAutomataSpace > & cellular_automata_space, unsigned int x, unsigned int y, unsigned int z)
{
	std::vector<unsigned int> neightborhood;
	return neightborhood;
}

void Neighborhood::setRadius(unsigned int r)
{
	if (r == 0) r = 1;
	radius = static_cast<int>(r);
}