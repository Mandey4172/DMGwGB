#include "VonNeummanNeighborhood.h"
#include"CellularAutomataSpace.h"


VonNeummanNeighborhood::VonNeummanNeighborhood()
{
}


VonNeummanNeighborhood::~VonNeummanNeighborhood()
{
}

std::vector<unsigned int> VonNeummanNeighborhood::get(CellularAutomataSpace * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
{
	std::vector<unsigned int> neighborhood;
	int m = static_cast<int>(cellularautomata->m),
		n = static_cast<int>(cellularautomata->n),
		o = static_cast<int>(cellularautomata->o);


	for (int i = -radius; i <= radius; i++)
	{
		int current_x = x + i;
		if (cellularautomata->getBoundatyConditionType() == BoundaryContidionTypes::Blocking && ((current_x < 0) || (current_x >= m)))
		{
			continue;
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
		if (cellularautomata->getCells()[current_x][y][z] > 0)
		{
			neighborhood.push_back(cellularautomata->getCells()[current_x][y][z]);
		}
	}
	for (int j = -radius; j <= radius; j++)
	{
		int current_y = y + j;
		if (cellularautomata->getBoundatyConditionType() == BoundaryContidionTypes::Blocking && ((current_y < 0 || current_y >= n)))
		{
			continue;
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
		if (cellularautomata->getCells()[x][current_y][z] > 0)
		{
			neighborhood.push_back(cellularautomata->getCells()[x][current_y][z]);
		}
	}
	for (int k = -radius; k <= radius; k++)
	{
		int current_z = z + k;
		if (cellularautomata->getBoundatyConditionType() == BoundaryContidionTypes::Blocking && ((current_z < 0) || (current_z >= o)))
		{
			continue;
		}
		else if (cellularautomata->getBoundatyConditionType() == BoundaryContidionTypes::Periodic)
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
		if (cellularautomata->getCells()[x][y][current_z] > 0)
		{
			neighborhood.push_back(cellularautomata->getCells()[x][y][current_z]);
		}
	}
	return neighborhood;
}
