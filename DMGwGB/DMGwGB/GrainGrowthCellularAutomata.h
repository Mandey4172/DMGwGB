#pragma once

#include "CellularAutomata.h"
#include "Neighborhood.h"
/**/

class GrainGrowthCellularAutomata :
	public CellularAutomata
{
public:
	GrainGrowthCellularAutomata();
	~GrainGrowthCellularAutomata();

	virtual bool step();
	virtual void start();
	
	int steps;
};

