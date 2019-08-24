#pragma once
#include "Neighborhood.h"

class RadialNeighborhood :
	public Neighborhood
{
public:
	RadialNeighborhood();
	~RadialNeighborhood();

	virtual std::vector<unsigned int> get(const std::shared_ptr<class CellularAutomataSpace > & cellular_automata_space, unsigned int x, unsigned int y, unsigned int z);
	/*virtual std::vector<unsigned int> fget(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z, std::list<std::array<int, 3>>  &queue);*/
};