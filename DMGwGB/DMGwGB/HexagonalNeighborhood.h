#pragma once
#include "Neighborhood.h"
class HexagonalNeighborhood :
	public Neighborhood
{
public:
	HexagonalNeighborhood();
	~HexagonalNeighborhood();
	
	/*virtual std::vector<int> get(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
private:
	std::vector<class Cell*> getXA(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<class Cell*> getXB(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<class Cell*> getYA(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<class Cell*> getYB(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<class Cell*> getZA(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<class Cell*> getZB(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);*/
};

