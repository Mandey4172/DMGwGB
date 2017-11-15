#pragma once

#include"Simulation.h"

ref class Calculations
{
public:
	Calculations();

	Simulation * simulation;

	void simulate();
};

