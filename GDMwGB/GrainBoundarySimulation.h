#pragma once
#include "Simulation.h"
class GrainBoundarySimulation :
	public Simulation
{
public:
	GrainBoundarySimulation();
	~GrainBoundarySimulation();

	Neighborhood * neighborhoodGrainBoundary;
	unsigned int grainSize;

	virtual bool step();
	virtual void start();
};

