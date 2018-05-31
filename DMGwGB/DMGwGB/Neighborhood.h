#pragma once

#include<vector>
#include<list>

class Neighborhood
{
public:
	Neighborhood();
	Neighborhood(const Neighborhood &o);
	~Neighborhood();

	bool isInited;

	virtual std::vector<unsigned int> get(class CellularAutomata * cellularautomata,unsigned int x, unsigned int y, unsigned int z);
};

