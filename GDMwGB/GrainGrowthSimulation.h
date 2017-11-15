#pragma once

#include "Simulation.h"

/**/
class GrainGrowthSimulation :
	public Simulation
{
public:
	GrainGrowthSimulation();
	~GrainGrowthSimulation();

	virtual bool step();
};

