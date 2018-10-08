#pragma once
#include "CellularAutomata.h"

class GrainGrowthWithBoundaryCellularAutomata :
	public CellularAutomata
{
public:
	GrainGrowthWithBoundaryCellularAutomata();

	unsigned int grainSize;
	class Neighborhood * boundary_neighborhood;

	virtual bool step() override;

	bool bFuseAfterSimulation;
};

