#include "MooreNeighborhood.h"
#include"CellularAutomata.h"

#include<array>

MooreNeighborhood::MooreNeighborhood()
{
}


MooreNeighborhood::~MooreNeighborhood()
{
}

std::vector<unsigned short> MooreNeighborhood::get(CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
{
	std::vector<unsigned short> neighborhood;
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
					for (int k = -1; k <= 1; k++)
					{
						if ((z + k >= 0) && (z + k < o))
						{
							if ((i != 0) || (j != 0) || (k != 0))
							{
								neighborhood.push_back(cellularautomata->getCells()[x + i][y + j][z + k]);
								if (cellularautomata->getCells()[x + i][y + j][z + k] == 0)
								{
									cellularautomata->front[x + i][y + j][z + k] = true;
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
		}
		else
		{
			continue;
		}
	}
	return neighborhood;
}

std::vector<unsigned short> MooreNeighborhood::fget(CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z, std::vector<std::array<int, 3>> &queue)
{
	std::vector<unsigned short> neighborhood;
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
					for (int k = -1; k <= 1; k++)
					{
						if ((z + k >= 0) && (z + k < o))
						{
							if ((i != 0) || (j != 0) || (k != 0))
							{
								neighborhood.push_back(cellularautomata->getCells()[x + i][y + j][z + k]);
								if (cellularautomata->getCells()[x + i][y + j][z + k] == 0)
								{
									std::array<int, 3>Point = { x + i, y + j, z + k };
									bool exist = false;
									for (std::array<int, 3> CPoint : queue)
									{
										if ((CPoint[0] == Point[0]) && (CPoint[1] == Point[1]) && (CPoint[2] == Point[2])) 
										{
											exist = true;
											break;
										}
									}
									if(!exist)
										queue.push_back(Point);
								}
							}
						}
					}
				}
			}
		}
	}
	return neighborhood;
}

