#include "VonNeummanNeighborhood.h"
#include"CellularAutomataSpace.h"

std::vector<unsigned int> VonNeummanNeighborhood::get(const std::shared_ptr< CellularAutomataSpace > & cellular_automata_space, unsigned int x, unsigned int y, unsigned int z) const
{
	std::vector<unsigned int> neighborhood;
	unsigned int m = static_cast<int>(cellular_automata_space->getSizeOnXAxis()),
				 n = static_cast<int>(cellular_automata_space->getSizeOnYAxis()),
				 o = static_cast<int>(cellular_automata_space->getSizeOnZAxis());

	for (int i = -radius; i <= radius; i++)
	{
		int current_x = x + i;
		if (cellular_automata_space->getBoundatyConditionType() == BoundaryContidionTypes::Blocking && ((static_cast<unsigned int>(current_x) < 0) || (static_cast<unsigned int>(current_x) >= m)))
		{
			continue;
		}
		else if (cellular_automata_space->getBoundatyConditionType() == BoundaryContidionTypes::Periodic)
		{
			if (static_cast<unsigned int>(current_x) < 0)
			{
				current_x = m + current_x;
			}
			else if (static_cast<unsigned int>(current_x) >= m)
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
			else if (static_cast<unsigned int>(current_x) >= m)
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
		if (cellular_automata_space->getBoundatyConditionType() == BoundaryContidionTypes::Blocking && ((static_cast<unsigned int>(current_y) < 0 || static_cast<unsigned int>(current_y) >= n)))
		{
			continue;
		}
		else if (cellular_automata_space->getBoundatyConditionType() == BoundaryContidionTypes::Periodic)
		{
			if (current_y < 0)
			{
				current_y = n + current_y;
			}
			else if (static_cast<unsigned int>(current_y) >= n)
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
			else if (static_cast<unsigned int>(current_y) >= n)
			{
				current_y = n - (current_y - n) - 1;
			}
		}
		if (cellular_automata_space->getCells()[x][static_cast<unsigned int>(current_y)][z] > 0)
		{
			neighborhood.push_back(cellular_automata_space->getCells()[x][current_y][z]);
		}
	}
	for (int k = -radius; k <= radius; k++)
	{
		int current_z = z + k;
		if (cellular_automata_space->getBoundatyConditionType() == BoundaryContidionTypes::Blocking && ((static_cast<unsigned int>(current_z) < 0) || (static_cast<unsigned int>(current_z) >= o)))
		{
			continue;
		}
		else if (cellular_automata_space->getBoundatyConditionType() == BoundaryContidionTypes::Periodic)
		{
			if (current_z < 0)
			{
				current_z = o + current_z;
			}
			else if (static_cast<unsigned int>(current_z) >= o)
			{
				current_z = current_z - o;
			}
		}
		else if (cellular_automata_space->getBoundatyConditionType() == BoundaryContidionTypes::Reflecting)
		{
			if (static_cast<unsigned int>(current_z) < 0)
			{
				current_z++;
				current_z = abs(current_z);
			}
			else if (static_cast<unsigned int>(current_z) >= o)
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