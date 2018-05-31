#include "PentagonalNeighborhood.h"
#include "CellularAutomata.h"

#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>

PentagonalNeighborhood::PentagonalNeighborhood()
{
}

std::vector<unsigned int> PentagonalNeighborhood::get(CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
{
	int v = rand() % 6;
	if (v == 0) return this->getFront(cellularautomata, x, y, z);
	else if (v == 1) return this->getBack(cellularautomata, x, y, z);
	else if (v == 2) return this->getLeft(cellularautomata, x, y, z);
	else if (v == 3) return this->getRight(cellularautomata, x, y, z);
	else if (v == 4) return this->getTop(cellularautomata, x, y, z);
	return this->getBottom(cellularautomata, x, y, z);
}

std::vector<unsigned int> PentagonalNeighborhood::getFront(CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
{
	std::vector<unsigned int> neighborhood;
	int m = cellularautomata->getSize()[0],
		n = cellularautomata->getSize()[1],
		o = cellularautomata->getSize()[2];

	for (int i = -1; i <= 0; i++)
	{
		int current_x = x + i;
		if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Blocking && ((current_x  < 0)  || (current_x >= m)))
		{
			continue;
		}
		if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Periodic)
		{
			if (current_x < 0)
			{
				current_x = m + current_x;
			}
			else if (current_x >= m)
			{
				current_x = current_x - m;
			}
		}
		for (int j = -1; j <= 1; j++)
		{
			int current_y = y + j;
			if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Blocking && ((current_y < 0) || (current_y >= n)))
			{
				continue;
			}
			else if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Periodic)
			{
				if (current_y < 0)
				{
					current_y = n + current_y;
				}
				else if (current_y >= n)
				{
					current_y = current_y - n;
				}
			}
			for (int k = -1; k <= 1; k++)
			{
				int current_z = z + k;
				if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Blocking && ((current_z < 0) || (current_z >= o)))
				{
					continue;
				}
				else if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Periodic)
				{
					if (current_z < 0)
					{
						current_z = o + current_z ;
					}
					else if (current_z >= o)
					{
						current_z = current_z - o;
					}
				}
				if ((i != 0) || (j != 0) || (k != 0))
				{
					if (cellularautomata->getCells()[current_x][current_y][current_z] != 0)
					{
						neighborhood.push_back(cellularautomata->getCells()[current_x][current_y][current_z]);
					}
					else
					{
						cellularautomata->front[current_x][current_y][current_z] = true;
					}
				}
			}
		}
	}
	return neighborhood;
}

std::vector<unsigned int> PentagonalNeighborhood::getBack(CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
{
	std::vector<unsigned int> neighborhood;
	int m = cellularautomata->getSize()[0],
		n = cellularautomata->getSize()[1],
		o = cellularautomata->getSize()[2];

	for (int i = 0; i <= 1; i++)
	{
		int current_x = x + i;
		if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Blocking && ((current_x  < 0)  || (current_x >= m)))
		{
			continue;
		}
		if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Periodic)
		{
			if (current_x < 0)
			{
				current_x = m + current_x;
			}
			else if (current_x >= m)
			{
				current_x = current_x - m;
			}
		}
		for (int j = -1; j <= 1; j++)
		{
			int current_y = y + j;
			if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Blocking && ((current_y < 0) || (current_y >= n)))
			{
				continue;
			}
			else if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Periodic)
			{
				if (current_y < 0)
				{
					current_y = n + current_y;
				}
				else if (current_y >= n)
				{
					current_y = current_y - n;
				}
			}
			for (int k = -1; k <= 1; k++)
			{
				int current_z = z + k;
				if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Blocking && ((current_z < 0) || (current_z >= o)))
				{
					continue;
				}
				else if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Periodic)
				{
					if (current_z < 0)
					{
						current_z = o + current_z ;
					}
					else if (current_z >= o)
					{
						current_z = current_z - o;
					}
				}
				if ((i != 0) || (j != 0) || (k != 0))
				{
					if (cellularautomata->getCells()[current_x][current_y][current_z] != 0)
					{
						neighborhood.push_back(cellularautomata->getCells()[current_x][current_y][current_z]);
					}
					else
					{
						cellularautomata->front[current_x][current_y][current_z] = true;
					}
				}
			}
		}
	}
	return neighborhood;
}

std::vector<unsigned int> PentagonalNeighborhood::getTop(CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
{
	std::vector<unsigned int> neighborhood;
	int m = cellularautomata->getSize()[0],
		n = cellularautomata->getSize()[1],
		o = cellularautomata->getSize()[2];

	for (int i = -1; i <= 1; i++)
	{
		int current_x = x + i;
		if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Blocking && ((current_x  < 0)  || (current_x >= m)))
		{
			continue;
		}
		if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Periodic)
		{
			if (current_x < 0)
			{
				current_x = m + current_x;
			}
			else if (current_x >= m)
			{
				current_x = current_x - m;
			}
		}
		for (int j = -1; j <= 0; j++)
		{
			int current_y = y + j;
			if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Blocking && ((current_y < 0) || (current_y >= n)))
			{
				continue;
			}
			else if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Periodic)
			{
				if (current_y < 0)
				{
					current_y = n + current_y;
				}
				else if (current_y >= n)
				{
					current_y = current_y - n;
				}
			}
			for (int k = -1; k <= 1; k++)
			{
				int current_z = z + k;
				if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Blocking && ((current_z < 0) || (current_z >= o)))
				{
					continue;
				}
				else if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Periodic)
				{
					if (current_z < 0)
					{
						current_z = o + current_z ;
					}
					else if (current_z >= o)
					{
						current_z = current_z - o;
					}
				}
				if ((i != 0) || (j != 0) || (k != 0))
				{
					if (cellularautomata->getCells()[current_x][current_y][current_z] != 0)
					{
						neighborhood.push_back(cellularautomata->getCells()[current_x][current_y][current_z]);
					}
					else
					{
						cellularautomata->front[current_x][current_y][current_z] = true;
					}
				}
			}
		}
	}
	return neighborhood;
}

std::vector<unsigned int> PentagonalNeighborhood::getBottom(CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
{
	std::vector<unsigned int> neighborhood;
	int m = cellularautomata->getSize()[0],
		n = cellularautomata->getSize()[1],
		o = cellularautomata->getSize()[2];

	for (int i = -1; i <= 1; i++)
	{
		int current_x = x + i;
		if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Blocking && ((current_x  < 0)  || (current_x >= m)))
		{
			continue;
		}
		if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Periodic)
		{
			if (current_x < 0)
			{
				current_x = m + current_x;
			}
			else if (current_x >= m)
			{
				current_x = current_x - m;
			}
		}
		for (int j = 0; j <= 1; j++)
		{
			int current_y = y + j;
			if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Blocking && ((current_y < 0) || (current_y >= n)))
			{
				continue;
			}
			else if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Periodic)
			{
				if (current_y < 0)
				{
					current_y = n + current_y;
				}
				else if (current_y >= n)
				{
					current_y = current_y - n;
				}
			}
			for (int k = -1; k <= 1; k++)
			{
				int current_z = z + k;
				if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Blocking && ((current_z < 0) || (current_z >= o)))
				{
					continue;
				}
				else if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Periodic)
				{
					if (current_z < 0)
					{
						current_z = o + current_z ;
					}
					else if (current_z >= o)
					{
						current_z = current_z - o;
					}
				}
				if ((i != 0) || (j != 0) || (k != 0))
				{
					if (cellularautomata->getCells()[current_x][current_y][current_z] != 0)
					{
						neighborhood.push_back(cellularautomata->getCells()[current_x][current_y][current_z]);
					}
					else
					{
						cellularautomata->front[current_x][current_y][current_z] = true;
					}
				}
			}
		}
	}
	return neighborhood;
}

std::vector<unsigned int> PentagonalNeighborhood::getLeft(CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
{
	std::vector<unsigned int> neighborhood;
	int m = cellularautomata->getSize()[0],
		n = cellularautomata->getSize()[1],
		o = cellularautomata->getSize()[2];

	for (int i = -1; i <= 1; i++)
	{
		int current_x = x + i;
		if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Blocking && ((current_x  < 0)  || (current_x >= m)))
		{
			continue;
		}
		if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Periodic)
		{
			if (current_x < 0)
			{
				current_x = m + current_x;
			}
			else if (current_x >= m)
			{
				current_x = current_x - m;
			}
		}
		for (int j = -1; j <= 1; j++)
		{
			int current_y = y + j;
			if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Blocking && ((current_y < 0) || (current_y >= n)))
			{
				continue;
			}
			else if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Periodic)
			{
				if (current_y < 0)
				{
					current_y = n + current_y;
				}
				else if (current_y >= n)
				{
					current_y = current_y - n;
				}
			}
			for (int k = -1; k <= 0; k++)
			{
				int current_z = z + k;
				if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Blocking && ((current_z < 0) || (current_z >= o)))
				{
					continue;
				}
				else if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Periodic)
				{
					if (current_z < 0)
					{
						current_z = o + current_z ;
					}
					else if (current_z >= o)
					{
						current_z = current_z - o;
					}
				}
				if ((i != 0) || (j != 0) || (k != 0))
				{
					if (cellularautomata->getCells()[current_x][current_y][current_z] != 0)
					{
						neighborhood.push_back(cellularautomata->getCells()[current_x][current_y][current_z]);
					}
					else
					{
						cellularautomata->front[current_x][current_y][current_z] = true;
					}
				}
			}
		}
	}
	return neighborhood;
}

std::vector<unsigned int> PentagonalNeighborhood::getRight(CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
{
	std::vector<unsigned int> neighborhood;
	int m = cellularautomata->getSize()[0],
		n = cellularautomata->getSize()[1],
		o = cellularautomata->getSize()[2];

	for (int i = -1; i <= 1; i++)
	{
		int current_x = x + i;
		if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Blocking && ((current_x  < 0)  || (current_x >= m)))
		{
			continue;
		}
		if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Periodic)
		{
			if (current_x < 0)
			{
				current_x = m + current_x;
			}
			else if (current_x >= m)
			{
				current_x = current_x - m;
			}
		}
		for (int j = -1; j <= 1; j++)
		{
			int current_y = y + j;
			if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Blocking && ((current_y < 0) || (current_y >= n)))
			{
				continue;
			}
			else if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Periodic)
			{
				if (current_y < 0)
				{
					current_y = n + current_y;
				}
				else if (current_y >= n)
				{
					current_y = current_y - n;
				}
			}
			for (int k = 0; k <= 1; k++)
			{
				int current_z = z + k;
				if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Blocking && ((current_z < 0) || (current_z >= o)))
				{
					continue;
				}
				else if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Periodic)
				{
					if (current_z < 0)
					{
						current_z = o + current_z ;
					}
					else if (current_z >= o)
					{
						current_z = current_z - o;
					}
				}
				if ((i != 0) || (j != 0) || (k != 0))
				{
					if (cellularautomata->getCells()[current_x][current_y][current_z] != 0)
					{
						neighborhood.push_back(cellularautomata->getCells()[current_x][current_y][current_z]);
					}
					else
					{
						cellularautomata->front[current_x][current_y][current_z] = true;
					}
				}
			}
		}
	}
	return neighborhood;
}
