#pragma once
#include "Neighborhood.h"
class HexagonalNeighborhood :
	public Neighborhood
{
public:
	HexagonalNeighborhood();
	~HexagonalNeighborhood();
	
	virtual std::vector<unsigned int> get(class CellularAutomataSpace * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
private:
	std::vector<unsigned int> getXA(class CellularAutomataSpace * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<unsigned int> getXB(class CellularAutomataSpace * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<unsigned int> getYA(class CellularAutomataSpace * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<unsigned int> getYB(class CellularAutomataSpace * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<unsigned int> getZA(class CellularAutomataSpace * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<unsigned int> getZB(class CellularAutomataSpace * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
};

