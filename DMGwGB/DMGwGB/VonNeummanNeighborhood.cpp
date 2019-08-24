#include "VonNeummanNeighborhood.h"
#include"CellularAutomataSpace.h"

VonNeummanNeighborhood::VonNeummanNeighborhood()
{
}

VonNeummanNeighborhood::~VonNeummanNeighborhood()
{
}

std::vector<unsigned int> VonNeummanNeighborhood::get(const std::shared_ptr< CellularAutomataSpace > & cellular_automata_space, unsigned int x, unsigned int y, unsigned int z)
{
	std::vector<unsigned int> neighborhood;
	int m = static_cast<int>(cellular_automata_space->m),
		n = static_cast<int>(cellular_automata_space->n),
		o = static_cast<int>(cellular_automata_space->o);

	for (int i = -radius; i <= radius; i++)
	{
		int current_x = x + i;
		if (cellular_automata_space->getBoundatyConditionType() == BoundaryContidionTypes::Blocking && ((current_x < 0) || (current_x >= m)))
		{
			continue;
		}
		else if (cellular_automata_space->getBoundatyConditionType() == BoundaryContidionTypes::Periodic)
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
		else if (cellular_automata_space->getBoundatyConditionType() == BoundaryContidionTypes::Reflecting)
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
		if (cellular_automata_space->getCells()[current_x][y][z] > 0)
		{
			neighborhood.push_back(cellular_automata_space->getCells()[current_x][y][z]);
		}
	}
	for (int j = -radius; j <= radius; j++)
	{
		int current_y = y + j;
		if (cellular_automata_space->getBoundatyConditionType() == BoundaryContidionTypes::Blocking && ((current_y < 0 || current_y >= n)))
		{
			continue;
		}
		else if (cellular_automata_space->getBoundatyConditionType() == BoundaryContidionTypes::Periodic)
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
		else if (cellular_automata_space->getBoundatyConditionType() == BoundaryContidionTypes::Reflecting)
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
		if (cellular_automata_space->getCells()[x][current_y][z] > 0)
		{
			neighborhood.push_back(cellular_automata_space->getCells()[x][current_y][z]);
		}
	}
	for (int k = -radius; k <= radius; k++)
	{
		int current_z = z + k;
		if (cellular_automata_space->getBoundatyConditionType() == BoundaryContidionTypes::Blocking && ((current_z < 0) || (current_z >= o)))
		{
			continue;
		}
		else if (cellular_automata_space->getBoundatyConditionType() == BoundaryContidionTypes::Periodic)
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
		else if (cellular_automata_space->getBoundatyConditionType() == BoundaryContidionTypes::Reflecting)
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
		if (cellular_automata_space->getCells()[x][y][current_z] > 0)
		{
			neighborhood.push_back(cellular_automata_space->getCells()[x][y][current_z]);
		}
	}
	return neighborhood;
}