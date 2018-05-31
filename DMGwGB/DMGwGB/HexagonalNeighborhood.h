#pragma once
#include "Neighborhood.h"
class HexagonalNeighborhood :
	public Neighborhood
{
public:
	HexagonalNeighborhood();
	~HexagonalNeighborhood();
	
	virtual std::vector<unsigned int> get(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
private:
	std::vector<unsigned int> getXA(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<unsigned int> getXB(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<unsigned int> getYA(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<unsigned int> getYB(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<unsigned int> getZA(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<unsigned int> getZB(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
};

