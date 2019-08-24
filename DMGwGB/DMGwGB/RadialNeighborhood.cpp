#include "RadialNeighborhood.h"
#include"CellularAutomataSpace.h"

RadialNeighborhood::RadialNeighborhood()
{
	radius = 1;
}

RadialNeighborhood::~RadialNeighborhood()
{
}

std::vector<unsigned int> RadialNeighborhood::get(const std::shared_ptr< CellularAutomataSpace > & cellular_automata_space, unsigned int x, unsigned int y, unsigned int z)
{
	std::vector<unsigned int> neighborhood;
	int m = static_cast<int>(cellular_automata_space->m),
		n = static_cast<int>(cellular_automata_space->n),
		o = static_cast<int>(cellular_automata_space->o);

	for (int i = -radius; i <= radius; i++)
	{
		int current_x = x + i;
		double r_x = static_cast<double>(current_x) - static_cast<double>(x);
		r_x = pow(r_x, 2);

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
			double r_y = static_cast<double>(current_y) - static_cast<double>(y);
			r_y = pow(r_y, 2);
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
				double r_z = static_cast<double>(current_z) - static_cast<double>(z);
				r_z = pow(r_z, 2);
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
				double r = r_x + r_y + r_z;
				double rad = pow(static_cast<double>(radius), 2);
				//r = sqrt(r);
				if ((r <= rad) && (cellular_automata_space->getCells()[current_x][current_y][current_z] > 0))
				{
					neighborhood.push_back(cellular_automata_space->getCells()[current_x][current_y][current_z]);
				}
			}
		}
	}
	if (neighborhood.empty()) return std::vector<unsigned int>();
	return neighborhood;
}