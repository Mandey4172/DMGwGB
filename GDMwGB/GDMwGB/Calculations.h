#pragma once

#include"Simulation.h"

class Calculations
{
public:
	Calculations();
	~Calculations();

	Simulation * simulation;

	void simulate();
};

