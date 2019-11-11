#include "Neighborhood.h"

//std::vector<unsigned int> Neighborhood::get(const std::shared_ptr<CellularAutomataSpace > & cellular_automata_space, unsigned int x, unsigned int y, unsigned int z) const
//{
//	std::vector<unsigned int> neightborhood;
//	return neightborhood;
//}

Neighborhood::Neighborhood()
{
}

Neighborhood::Neighborhood(const Neighborhood& other)
{
	radius = other.radius;
}

Neighborhood::Neighborhood(Neighborhood&& other)
{
	std::swap(radius, other.radius);
}

Neighborhood& Neighborhood::operator=(const Neighborhood& other)
{
	radius = other.radius;
}

Neighborhood& Neighborhood::operator=(Neighborhood&& other)
{
	std::swap(radius, other.radius);
	return *this;
}

Neighborhood::~Neighborhood() {}

void Neighborhood::setRadius(unsigned int r)
{
	if (r == 0) r = 1;
	radius = static_cast<int>(r);
}