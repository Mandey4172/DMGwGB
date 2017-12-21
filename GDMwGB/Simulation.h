#pragma once

/**/
class Simulation
{
public:
	Simulation();

	virtual bool step();
	virtual void start();

	class CellularAutomata * cellularautomata;
	class CRule * rule;
	class Neighborhood * neighborhood;
};

