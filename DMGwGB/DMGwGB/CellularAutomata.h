#pragma once

/**/
class CellularAutomata
{
public:
	CellularAutomata();
	virtual ~CellularAutomata();

	virtual bool step();
	void start();

	class CellularAutomataSpace * cellularautomata;
	class Neighborhood * neighborhood;

protected:
	class CellularAutomataRule * rule;
};

