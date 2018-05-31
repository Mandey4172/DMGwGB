#pragma once
#include"Neighborhood.h"


class PentagonalNeighborhood : public Neighborhood
{
public:
	PentagonalNeighborhood();
	
	virtual std::vector<unsigned int> get(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
private:
	std::vector<unsigned int> getFront(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<unsigned int> getBack(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<unsigned int> getLeft(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<unsigned int> getRight(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<unsigned int> getTop(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<unsigned int> getBottom(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
};

