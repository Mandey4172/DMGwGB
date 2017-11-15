#pragma once
#include "Simulation.h"
class GrainBoundarySimulation :
	public Simulation
{
public:
	GrainBoundarySimulation();
	~GrainBoundarySimulation();

	virtual bool step();
};

