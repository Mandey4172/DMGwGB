#pragma once
#include "Neighborhood.h"
class VonNeummanNeighborhood :
	public Neighborhood
{
public:
	std::vector<unsigned int> get(const std::shared_ptr<class CellularAutomataSpace > & cellular_automata_space, unsigned int x, unsigned int y, unsigned int z) const override;
};
