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
	~GrainGrowthCellularAutomata();

	virtual bool step() override;
};

