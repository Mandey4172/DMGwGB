#pragma once
#include "CellularAutomata.h"

class GrainBoundaryGrowthCellularAutomata :
	public CellularAutomata
{
public:
	GrainBoundaryGrowthCellularAutomata();

	unsigned int grainSize;

	virtual bool step();
	virtual void start();
};

