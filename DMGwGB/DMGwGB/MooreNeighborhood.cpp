#include "MooreNeighborhood.h"
#include"CellularAutomataSpace.h"

#include<array>
#include<list>


std::vector<unsigned int> MooreNeighborhood::get(const std::shared_ptr< CellularAutomataSpace > & cellular_automata_space, unsigned int x, unsigned int y, unsigned int z) const 
{
	std::vector<unsigned int> neighborhood;
	int m = static_cast<int>(cellular_automata_space->getSizeOnXAxis()),
		n = static_cast<int>(cellular_automata_space->getSizeOnYAxis()),
		o = static_cast<int>(cellular_automata_space->getSizeOnZAxis());

	for (int i = -radius; i <= radius; i++)
	{
		int current_x = x + i;
		if (cellular_automata_space->getBoundatyConditionType() == BoundaryContidionTypes::Blocking)
		{
			if (current_x < 0 || current_x >= m)
			{
				continue;
			}
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
		for (int j = -radius; j <= radius; j++)
		{
			int current_y = y + j;
			if (cellular_automata_space->getBoundatyConditionType() == BoundaryContidionTypes::Blocking)
			{
				if ((current_y < 0) || (current_y >= n))
				{
					continue;
				}
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
			for (int k = -radius; k <= radius; k++)
			{
				int current_z = z + k;
				if (cellular_automata_space->getBoundatyConditionType() == BoundaryContidionTypes::Blocking)
				{
					if ((current_z < 0) || (current_z >= o))
					{
						continue;
					}
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
				if (cellular_automata_space->getCells()[current_x][current_y][current_z] > 0)
				{
					neighborhood.push_back(cellular_automata_space->getCells()[current_x][current_y][current_z]);
				}
			}
		}
	}
	if (neighborhood.empty()) return std::vector<unsigned int>();
	return neighborhood;
}