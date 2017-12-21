#pragma once
#include "Neighborhood.h"
class VonNeummanNeighborhood :
	public Neighborhood
{
public:
	VonNeummanNeighborhood();
	~VonNeummanNeighborhood();

	virtual std::vector<class Cell*> get(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
};

