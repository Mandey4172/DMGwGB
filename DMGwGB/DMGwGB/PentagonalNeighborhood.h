#pragma once
#include"Neighborhood.h"


class PentagonalNeighborhood : public Neighborhood
{
public:
	PentagonalNeighborhood();
	
	virtual std::vector<unsigned int> get(class CellularAutomataSpace * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
private:
	std::vector<unsigned int> getFront(class CellularAutomataSpace * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<unsigned int> getBack(class CellularAutomataSpace * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<unsigned int> getLeft(class CellularAutomataSpace * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<unsigned int> getRight(class CellularAutomataSpace * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<unsigned int> getTop(class CellularAutomataSpace * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
	std::vector<unsigned int> getBottom(class CellularAutomataSpace * cellularautomata, unsigned int x, unsigned int y, unsigned int z);
};

