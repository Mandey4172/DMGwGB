#pragma once

#include<vector>

class Neighborhood
{
public:
	Neighborhood();
	~Neighborhood();

	virtual std::vector<class Cell> get(class CellularAutomata * cellularautomata,unsigned int x, unsigned int y, unsigned int z);
};

