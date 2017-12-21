#include "MooreNeighborhood.h"
#include"CellularAutomata.h"


MooreNeighborhood::MooreNeighborhood()
{
}


MooreNeighborhood::~MooreNeighborhood()
{
}

std::vector<class Cell*> MooreNeighborhood::get(CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
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
					for (int k = -1; k <= 1; k++)
					{
						if ((z + k >= 0) && (z + k < o))
						{
							if ((i != 0) || (j != 0) || (k != 0))
							{
								neighborhood.push_back(&cellularautomata->getCells()[x + i][y + j][z + k]);
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
