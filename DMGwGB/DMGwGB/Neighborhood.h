#pragma once

#include<vector>
#include<list>

class Neighborhood
{
public:
	Neighborhood();
	Neighborhood(const Neighborhood &o);
	~Neighborhood();

	//Pobieranie s¹siadów
	virtual std::vector<unsigned int> get(class CellularAutomata * cellularautomata,unsigned int x, unsigned int y, unsigned int z);
};

