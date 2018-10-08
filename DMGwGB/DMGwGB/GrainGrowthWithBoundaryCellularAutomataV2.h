#pragma once
#include "CellularAutomata.h"

class GrainGrowthWithBoundaryCellularAutomataV2 :
	public CellularAutomata
{
public:
	GrainGrowthWithBoundaryCellularAutomataV2();
	~GrainGrowthWithBoundaryCellularAutomataV2();

	unsigned int grainSize;
	class Neighborhood * boundary_neighborhood;

	virtual bool step();
	//virtual void start();

	bool bFuseAfterSimulation;
};

