#pragma once

#include"CellularAutomata.h"

class Calculations
{
public:
	Calculations();
	~Calculations();

	CellularAutomata * simulation;

	void simulate();
};

