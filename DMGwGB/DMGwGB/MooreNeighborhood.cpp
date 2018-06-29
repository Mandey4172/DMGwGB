#include "MooreNeighborhood.h"
#include"CellularAutomata.h"

#include<array>
#include<list>
MooreNeighborhood::MooreNeighborhood()
{
}

MooreNeighborhood::~MooreNeighborhood()
{
}

std::vector<unsigned int> MooreNeighborhood::get(CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
{
	std::vector<unsigned int> neighborhood;
	int m = static_cast<int>(cellularautomata->getSize()[0]),
		n = static_cast<int>(cellularautomata->getSize()[1]),
		o = static_cast<int>(cellularautomata->getSize()[2]);

	for (int i = -1; i <= 1; i++)
	{
		int current_x = x + i;
		if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Blocking)
		{
			if (current_x < 0 || current_x >= m)
			{
				continue;
			}
		}
		else if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Periodic)
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
		else if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Reflecting)
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
		for (int j = -1; j <= 1; j++)
		{
			int current_y = y + j;
			if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Blocking)
			{
				if ((current_y < 0) || (current_y >= n))
				{
					continue;
				}
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
			else if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Reflecting)
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
			for (int k = -1; k <= 1; k++)
			{
				int current_z = z + k;
				if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Blocking)
				{
					if ((current_z < 0) || (current_z >= o))
					{
						continue;
					}
				}
				else if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Periodic)
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
				else if (cellularautomata->boundary_contidion == BoundaryContidionTypes::Reflecting)
				{
					if (current_z < 0)
					{
						current_z++;
						current_z = abs(current_z);
					}
					else if (current_z >= o)
					{
						current_z = o - (current_z - o);
					}
				}
				if (cellularautomata->getCells()[current_x][current_y][current_z] > 0)
				{
					neighborhood.push_back(cellularautomata->getCells()[current_x][current_y][current_z]);
				}
				else if (cellularautomata->getCells()[current_x][current_y][current_z] == 0)
				{
					cellularautomata->front[current_x][current_y][current_z] = true;
				}
			}
		}
	}
	return neighborhood;
}
