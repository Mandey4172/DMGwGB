#pragma once
#include "Neighborhood.h"

class RadialNeighborhood :
	public Neighborhood
{
public:
	RadialNeighborhood();
	~RadialNeighborhood();

	virtual std::vector<unsigned int> get(class CellularAutomataSpace * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	/*virtual std::vector<unsigned int> fget(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z, std::list<std::array<int, 3>>  &queue);*/
};