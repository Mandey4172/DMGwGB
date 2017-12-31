#pragma once
#include "Neighborhood.h"

class NVonNeummanNeighborhood :
	public Neighborhood
{
public:
	NVonNeummanNeighborhood();
	~NVonNeummanNeighborhood();

	virtual std::vector<class Cell*> get(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
};

