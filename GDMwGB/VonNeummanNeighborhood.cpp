#include "VonNeummanNeighborhood.h"
#include"CellularAutomata.h"


VonNeummanNeighborhood::VonNeummanNeighborhood()
{
}


VonNeummanNeighborhood::~VonNeummanNeighborhood()
{
}

std::vector<class Cell> VonNeummanNeighborhood::get(CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
{
	std::vector<Cell> neighborhood;
	int m = cellularautomata->getSize()[0],
		n = cellularautomata->getSize()[1],
		o = cellularautomata->getSize()[2];

	for (int i = -1; i <= 1; i++)
	{
		if ((x + i >= 0) && (x + i < m))
		{
			if (cellularautomata->getCells()[x + i][y][z].getState() != 0)
			neighborhood.push_back(cellularautomata->getCells()[x + i][y][z]);
		}
		else
		{
			continue;
		}
	}
	for (int j = -1; j <= 1; j++)
	{
		if ((y + j >= 0) && (y + j < n))
		{
			if (cellularautomata->getCells()[x][y + j][z].getState() != 0)
				neighborhood.push_back(cellularautomata->getCells()[x][y + j][z]);
		}
		else
		{
			continue;
		}
	}
	for (int k = -1; k <= 1; k++)
	{
		if ((z + k >= 0) && (z + k < o))
		{
			if (cellularautomata->getCells()[x][y][z + k].getState() != 0)
				neighborhood.push_back(cellularautomata->getCells()[x][y][z + k]);
		}
		else
		{
			continue;
		}
	}
	return neighborhood;
}
