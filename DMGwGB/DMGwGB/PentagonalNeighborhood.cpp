#include "PentagonalNeighborhood.h"
#include "CellularAutomataSpace.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

std::vector<unsigned int> PentagonalNeighborhood::get(const std::shared_ptr< CellularAutomataSpace >& cellular_automata_space, unsigned int x, unsigned int y, unsigned int z) const
{
	int v = rand() % 6;
	if (v == 0) return getFront(cellular_automata_space, x, y, z);
	else if (v == 1) return getBack(cellular_automata_space, x, y, z);
	else if (v == 2) return getLeft(cellular_automata_space, x, y, z);
	else if (v == 3) return getRight(cellular_automata_space, x, y, z);
	else if (v == 4) return getTop(cellular_automata_space, x, y, z);
	return getBottom(cellular_automata_space, x, y, z);
}

std::vector<unsigned int> PentagonalNeighborhood::getFront(const std::shared_ptr< CellularAutomataSpace >& cellular_automata_space, unsigned int x, unsigned int y, unsigned int z) const
{
	std::vector<unsigned int> neighborhood;

	int m = static_cast<int>(cellular_automata_space->getSizeOnXAxis()),
		n = static_cast<int>(cellular_automata_space->getSizeOnYAxis()),
		o = static_cast<int>(cellular_automata_space->getSizeOnZAxis());

	for (int i = -radius; i <= 0; i++)
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
		for (int j = -radius; j <= radius; j++)
		{
			int current_y = y + j;
			if (cellular_automata_space->getBoundatyConditionType() == BoundaryContidionTypes::Blocking && ((current_y < 0) || (current_y >= n)))
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
				if (cellular_automata_space->getCells()[current_x][current_y][current_z] != 0)
				{
					neighborhood.push_back(cellular_automata_space->getCells()[current_x][current_y][current_z]);
				}
			}
		}
	}
	return neighborhood;
}

std::vector<unsigned int> PentagonalNeighborhood::getBack(const std::shared_ptr< CellularAutomataSpace >& cellular_automata_space, unsigned int x, unsigned int y, unsigned int z) const
{
	std::vector<unsigned int> neighborhood;
	int m = static_cast<int>(cellular_automata_space->getSizeOnXAxis()),
		n = static_cast<int>(cellular_automata_space->getSizeOnYAxis()),
		o = static_cast<int>(cellular_automata_space->getSizeOnZAxis());

	for (int i = 0; i <= radius; i++)
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
		for (int j = -radius; j <= radius; j++)
		{
			int current_y = y + j;
			if (cellular_automata_space->getBoundatyConditionType() == BoundaryContidionTypes::Blocking && ((current_y < 0) || (current_y >= n)))
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
				if (cellular_automata_space->getCells()[current_x][current_y][current_z] != 0)
				{
					neighborhood.push_back(cellular_automata_space->getCells()[current_x][current_y][current_z]);
				}
			}
		}
	}
	return neighborhood;
}

std::vector<unsigned int> PentagonalNeighborhood::getTop(const std::shared_ptr< CellularAutomataSpace >& cellular_automata_space, unsigned int x, unsigned int y, unsigned int z) const
{
	std::vector<unsigned int> neighborhood;
	int m = static_cast<int>(cellular_automata_space->getSizeOnXAxis()),
		n = static_cast<int>(cellular_automata_space->getSizeOnYAxis()),
		o = static_cast<int>(cellular_automata_space->getSizeOnZAxis());

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
		for (int j = -radius; j <= 0; j++)
		{
			int current_y = y + j;
			if (cellular_automata_space->getBoundatyConditionType() == BoundaryContidionTypes::Blocking && ((current_y < 0) || (current_y >= n)))
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
				if (cellular_automata_space->getCells()[current_x][current_y][current_z] != 0)
				{
					neighborhood.push_back(cellular_automata_space->getCells()[current_x][current_y][current_z]);
				}
			}
		}
	}
	return neighborhood;
}

std::vector<unsigned int> PentagonalNeighborhood::getBottom(const std::shared_ptr< CellularAutomataSpace >& cellular_automata_space, unsigned int x, unsigned int y, unsigned int z) const
{
	std::vector<unsigned int> neighborhood;
	int m = static_cast<int>(cellular_automata_space->getSizeOnXAxis()),
		n = static_cast<int>(cellular_automata_space->getSizeOnYAxis()),
		o = static_cast<int>(cellular_automata_space->getSizeOnZAxis());

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
		for (int j = 0; j <= radius; j++)
		{
			int current_y = y + j;
			if (cellular_automata_space->getBoundatyConditionType() == BoundaryContidionTypes::Blocking && ((current_y < 0) || (current_y >= n)))
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
				if (cellular_automata_space->getCells()[current_x][current_y][current_z] != 0)
				{
					neighborhood.push_back(cellular_automata_space->getCells()[current_x][current_y][current_z]);
				}
			}
		}
	}
	return neighborhood;
}

std::vector<unsigned int> PentagonalNeighborhood::getLeft(const std::shared_ptr< CellularAutomataSpace >& cellular_automata_space, unsigned int x, unsigned int y, unsigned int z) const
{
	std::vector<unsigned int> neighborhood;
	int m = static_cast<int>(cellular_automata_space->getSizeOnXAxis()),
		n = static_cast<int>(cellular_automata_space->getSizeOnYAxis()),
		o = static_cast<int>(cellular_automata_space->getSizeOnZAxis());

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
		for (int j = -radius; j <= radius; j++)
		{
			int current_y = y + j;
			if (cellular_automata_space->getBoundatyConditionType() == BoundaryContidionTypes::Blocking && ((current_y < 0) || (current_y >= n)))
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
			for (int k = -radius; k <= 0; k++)
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
				if (cellular_automata_space->getCells()[current_x][current_y][current_z] != 0)
				{
					neighborhood.push_back(cellular_automata_space->getCells()[current_x][current_y][current_z]);
				}
			}
		}
	}
	return neighborhood;
}

std::vector<unsigned int> PentagonalNeighborhood::getRight(const std::shared_ptr< CellularAutomataSpace >& cellular_automata_space, unsigned int x, unsigned int y, unsigned int z) const
{
	std::vector<unsigned int> neighborhood;
	int m = static_cast<int>(cellular_automata_space->getSizeOnXAxis()),
		n = static_cast<int>(cellular_automata_space->getSizeOnYAxis()),
		o = static_cast<int>(cellular_automata_space->getSizeOnZAxis());

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
		for (int j = -radius; j <= radius; j++)
		{
			int current_y = y + j;
			if (cellular_automata_space->getBoundatyConditionType() == BoundaryContidionTypes::Blocking && ((current_y < 0) || (current_y >= n)))
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
			for (int k = 0; k <= radius; k++)
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
				if (cellular_automata_space->getCells()[current_x][current_y][current_z] != 0)
				{
					neighborhood.push_back(cellular_automata_space->getCells()[current_x][current_y][current_z]);
				}
			}
		}
	}
	return neighborhood;
}