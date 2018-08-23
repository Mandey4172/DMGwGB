#pragma once

/**/
class CellularAutomata
{
public:
	CellularAutomata();
	virtual ~CellularAutomata();

	virtual bool step();
	virtual void start();

	class CellularAutomataSpace * cellularautomata;
	class Neighborhood * neighborhood;

protected:
	class CRule * rule;
};

