#pragma once

#include "Simulation.h"
#include "Neighborhood.h"
/**/

class GrainGrowthSimulation :
	public Simulation
{
public:
	GrainGrowthSimulation();
	~GrainGrowthSimulation();

	virtual bool step();
	virtual void start();
	std::vector<class Cell *> queue;
	int steps;
};

