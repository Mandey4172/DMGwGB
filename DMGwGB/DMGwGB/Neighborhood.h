#pragma once

#include<vector>

class Neighborhood
{
public:
	Neighborhood();
	Neighborhood(const Neighborhood &o);
	~Neighborhood();

	virtual std::vector<unsigned short> get(class CellularAutomata * cellularautomata,unsigned int x, unsigned int y, unsigned int z);
};
