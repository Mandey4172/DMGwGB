#include "PentagonalNeighborhood.h"
#include "CellularAutomata.h"

#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>

PentagonalNeighborhood::PentagonalNeighborhood()
{
}

//std::vector<class Cell*> PentagonalNeighborhood::get(CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
//{
//	int v = rand() % 6;
//	if (v == 0) return this->getFront(cellularautomata, x, y, z);
//	else if (v == 1) return this->getBack(cellularautomata, x, y, z);
//	else if (v == 2) return this->getLeft(cellularautomata, x, y, z);
//	else if (v == 3) return this->getRight(cellularautomata, x, y, z);
//	else if (v == 4) return this->getTop(cellularautomata, x, y, z);
//	else if (v == 5) return this->getBottom(cellularautomata, x, y, z);
//	return std::vector<class Cell*>();
//}

std::vector<class Cell*> PentagonalNeighborhood::getFront(CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
{
	std::vector<Cell*> neighborhood;
	int m = cellularautomata->getSize()[0],
		n = cellularautomata->getSize()[1],
		o = cellularautomata->getSize()[2];

	for (int i = -1; i <= 0; i++)
	{
		if ((x + i >= 0) && (x + i < m))
		{
			for (int j = -1; j <= 1; j++)
			{
				if ((y + j >= 0) && (y + j < n))
				{
					for (int k = -1; k <= 1; k++)
					{
						if ((z + k >= 0) && (z + k < o))
						{
							if ((i != 0) || (j != 0) || (k != 0))
							{
								/*if (cellularautomata->getCells()[x + i][y + j][z + k].getState() != 0)
									neighborhood.push_back(&cellularautomata->getCells()[x + i][y + j][z + k]);*/
							}
						}
						else
						{
							continue;
						}
					}
				}
				else
				{
					continue;
				}
			}
		}
		else
		{
			continue;
		}
	}
	return neighborhood;
}

std::vector<class Cell*> PentagonalNeighborhood::getBack(CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
{
	std::vector<Cell*> neighborhood;
	int m = cellularautomata->getSize()[0],
		n = cellularautomata->getSize()[1],
		o = cellularautomata->getSize()[2];

	for (int i = 0; i <= 1; i++)
	{
		if ((x + i >= 0) && (x + i < m))
		{
			for (int j = -1; j <= 1; j++)
			{
				if ((y + j >= 0) && (y + j < n))
				{
					for (int k = -1; k <= 1; k++)
					{
						if ((z + k >= 0) && (z + k < o))
						{
							if ((i != 0) || (j != 0) || (k != 0))
							{
								/*if (cellularautomata->getCells()[x + i][y + j][z + k].getState() != 0)
									neighborhood.push_back(&cellularautomata->getCells()[x + i][y + j][z + k]);*/
							}
						}
						else
						{
							continue;
						}
					}
				}
				else
				{
					continue;
				}
			}
		}
		else
		{
			continue;
		}
	}
	return neighborhood;
}

std::vector<class Cell*> PentagonalNeighborhood::getTop(CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
{
	std::vector<Cell*> neighborhood;
	int m = cellularautomata->getSize()[0],
		n = cellularautomata->getSize()[1],
		o = cellularautomata->getSize()[2];

	for (int i = -1; i <= 1; i++)
	{
		if ((x + i >= 0) && (x + i < m))
		{
			for (int j = -1; j <= 0; j++)
			{
				if ((y + j >= 0) && (y + j < n))
				{
					for (int k = -1; k <= 1; k++)
					{
						if ((z + k >= 0) && (z + k < o))
						{
							if ((i != 0) || (j != 0) || (k != 0))
							{
								/*if (cellularautomata->getCells()[x + i][y + j][z + k].getState() != 0)
									neighborhood.push_back(&cellularautomata->getCells()[x + i][y + j][z + k]);*/
							}
						}
						else
						{
							continue;
						}
					}
				}
				else
				{
					continue;
				}
			}
		}
		else
		{
			continue;
		}
	}
	return neighborhood;
}

std::vector<class Cell*> PentagonalNeighborhood::getBottom(CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
{
	std::vector<Cell*> neighborhood;
	int m = cellularautomata->getSize()[0],
		n = cellularautomata->getSize()[1],
		o = cellularautomata->getSize()[2];

	for (int i = -1; i <= 1; i++)
	{
		if ((x + i >= 0) && (x + i < m))
		{
			for (int j = 0; j <= 1; j++)
			{
				if ((y + j >= 0) && (y + j < n))
				{
					for (int k = -1; k <= 1; k++)
					{
						if ((z + k >= 0) && (z + k < o))
						{
							if ((i != 0) || (j != 0) || (k != 0))
							{
								/*if (cellularautomata->getCells()[x + i][y + j][z + k].getState() != 0)
									neighborhood.push_back(&cellularautomata->getCells()[x + i][y + j][z + k]);*/
							}
						}
						else
						{
							continue;
						}
					}
				}
				else
				{
					continue;
				}
			}
		}
		else
		{
			continue;
		}
	}
	return neighborhood;
}

std::vector<class Cell*> PentagonalNeighborhood::getLeft(CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
{
	std::vector<Cell*> neighborhood;
	int m = cellularautomata->getSize()[0],
		n = cellularautomata->getSize()[1],
		o = cellularautomata->getSize()[2];

	for (int i = -1; i <= 1; i++)
	{
		if ((x + i >= 0) && (x + i < m))
		{
			for (int j = -1; j <= 1; j++)
			{
				if ((y + j >= 0) && (y + j < n))
				{
					for (int k = -1; k <= 0; k++)
					{
						if ((z + k >= 0) && (z + k < o))
						{
							if ((i != 0) || (j != 0) || (k != 0))
							{
								/*if (cellularautomata->getCells()[x + i][y + j][z + k].getState() != 0)
									neighborhood.push_back(&cellularautomata->getCells()[x + i][y + j][z + k]);*/
							}
						}
						else
						{
							continue;
						}
					}
				}
				else
				{
					continue;
				}
			}
		}
		else
		{
			continue;
		}
	}
	return neighborhood;
}

std::vector<class Cell*> PentagonalNeighborhood::getRight(CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
{
	std::vector<Cell*> neighborhood;
	int m = cellularautomata->getSize()[0],
		n = cellularautomata->getSize()[1],
		o = cellularautomata->getSize()[2];

	for (int i = -1; i <= 1; i++)
	{
		if ((x + i >= 0) && (x + i < m))
		{
			for (int j = -1; j <= 1; j++)
			{
				if ((y + j >= 0) && (y + j < n))
				{
					for (int k = 0; k <= 1; k++)
					{
						if ((z + k >= 0) && (z + k < o))
						{
							if ((i != 0) || (j != 0) || (k != 0))
							{
								/*if (cellularautomata->getCells()[x + i][y + j][z + k].getState() != 0)
									neighborhood.push_back(&cellularautomata->getCells()[x + i][y + j][z + k]);*/
							}
						}
						else
						{
							continue;
						}
					}
				}
				else
				{
					continue;
				}
			}
		}
		else
		{
			continue;
		}
	}
	return neighborhood;
}
