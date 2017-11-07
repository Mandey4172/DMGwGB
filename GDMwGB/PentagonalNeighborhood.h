#pragma once
#include"Neighborhood.h"


class PentagonalNeighborhood : public Neighborhood
{
public:
	PentagonalNeighborhood();
	
	virtual std::vector<class Cell> get(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
private:
	std::vector<class Cell> getFront(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<class Cell> getBack(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<class Cell> getLeft(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<class Cell> getRight(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<class Cell> getTop(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<class Cell> getBottom(class CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
};

