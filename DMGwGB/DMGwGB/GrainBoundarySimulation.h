#pragma once
#include "Simulation.h"
class GrainBoundarySimulation :
	public Simulation
{
public:
	GrainBoundarySimulation();

	unsigned int grainSize;
	unsigned int clearIterations;

	virtual bool step();
	virtual void start();
};

