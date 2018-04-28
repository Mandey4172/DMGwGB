#pragma once
#include "Neighborhood.h"

class MooreNeighborhood :
	public Neighborhood
{
public:
	MooreNeighborhood();
	~MooreNeighborhood();

	virtual std::vector<unsigned short> get(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	virtual std::vector<unsigned short> fget(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z, std::list<std::array<int, 3>>  &queue);
};

