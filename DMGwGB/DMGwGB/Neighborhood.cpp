#include "Neighborhood.h"

#include"Cell.h"


Neighborhood::Neighborhood()
{
	isInited = false;
}

Neighborhood::Neighborhood(const Neighborhood & o)
{
}


Neighborhood::~Neighborhood()
{
}

std::vector<unsigned int> Neighborhood::get(CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
{
	return std::vector<unsigned int>();
}




