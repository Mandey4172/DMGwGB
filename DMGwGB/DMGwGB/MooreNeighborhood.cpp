#include "MooreNeighborhood.h"
#include"CellularAutomataSpace.h"

#include<array>
#include<list>
MooreNeighborhood::MooreNeighborhood()
{
}

MooreNeighborhood::~MooreNeighborhood()
{
}

std::vector<unsigned int> MooreNeighborhood::get(CellularAutomataSpace * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
{
	std::vector<unsigned int> neighborhood;
	int m = static_cast<int>(cellularautomata->m),
		n = static_cast<int>(cellularautomata->n),
		o = static_cast<int>(cellularautomata->o);

	for (int i = -radius; i <= radius; i++)
	{
		int current_x = x + i;
		if (cellularautomata->getBoundatyConditionType() == BoundaryContidionTypes::Blocking)
		{
			if (current_x < 0 || current_x >= m)
			{
				continue;
			}
		}
		else if (cellularautomata->getBoundatyConditionType() == BoundaryContidionTypes::Periodic)
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
		else if (cellularautomata->getBoundatyConditionType() == BoundaryContidionTypes::Reflecting)
		{
			if (current_x < 0)
			{
				current_x++;
				current_x = abs(current_x);
			}
			else if (current_x >= m)
			{
				current_x = m - (current_x - m) - 1;
			}
		}
		for (int j = -radius; j <= radius; j++)
		{
			int current_y = y + j;
			if (cellularautomata->getBoundatyConditionType() == BoundaryContidionTypes::Blocking)
			{
				if ((current_y < 0) || (current_y >= n))
				{
					continue;
				}
			}
			else if (cellularautomata->getBoundatyConditionType() == BoundaryContidionTypes::Periodic)
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
			else if (cellularautomata->getBoundatyConditionType() == BoundaryContidionTypes::Reflecting)
			{
				if (current_y < 0)
				{
					current_y++;
					current_y = abs(current_y);
				}
				else if (current_y >= n)
				{
					current_y = n - (current_y - n) - 1;
				}
			}
			for (int k = -radius; k <= radius; k++)
			{
				int current_z = z + k;
				if (cellularautomata->getBoundatyConditionType() == BoundaryContidionTypes::Blocking)
				{
					if ((current_z < 0) || (current_z >= o))
					{
						continue;
					}
				}
				else if (cellularautomata->getBoundatyConditionType() == BoundaryContidionTypes::Periodic)
				{
					if (current_z < 0)
					{
						current_z = o + current_z;
					}
					else if (current_z >= o)
					{
						current_z = current_z - o;
					}
				}
				else if (cellularautomata->getBoundatyConditionType() == BoundaryContidionTypes::Reflecting)
				{
					if (current_z < 0)
					{
						current_z++;
						current_z = abs(current_z);
					}
					else if (current_z >= o)
					{
						current_z = o - (current_z - o) - 1;
					}
				}
				if (cellularautomata->getCells()[current_x][current_y][current_z] > 0)
				{
					neighborhood.push_back(cellularautomata->getCells()[current_x][current_y][current_z]);
				}
			}
		}
	}
	if (neighborhood.empty()) return std::vector<unsigned int>();
	return neighborhood;
}
