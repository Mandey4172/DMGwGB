#pragma once
#include "Simulation.h"
class FGrainGrowthSimulation :
	public Simulation
{
public:
	FGrainGrowthSimulation();
	~FGrainGrowthSimulation();

	virtual bool step();
	virtual void start();
};

