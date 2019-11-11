#pragma once

#include "CellularAutomata.h"
#include "Neighborhood.h"

/**/
//Simulation of grain growth
class GrainGrowthCellularAutomata :
	public CellularAutomata
{
public:
	GrainGrowthCellularAutomata();

	bool step() override;
};

