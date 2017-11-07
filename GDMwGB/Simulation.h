#pragma once
class Simulation
{
public:
	Simulation();

	void step();
public:
	class Neighborhood * neighborhood;
	class CRule * rule;
	class CellularAutomata * cellularautomata;
};

