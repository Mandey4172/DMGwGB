#include "HexagonalNeighborhood.h"
#include "CellularAutomataSpace.h"

HexagonalNeighborhood::HexagonalNeighborhood()
{
}

HexagonalNeighborhood::~HexagonalNeighborhood()
{
}

std::vector<unsigned int> HexagonalNeighborhood::get(const std::shared_ptr< CellularAutomataSpace > & cellular_automata_space, unsigned int x, unsigned int y, unsigned int z) const
{
	int v = rand() % 6;
	if (v == 0) return getXA(cellular_automata_space, x, y, z);
	else if (v == 1) return getXB(cellular_automata_space, x, y, z);
	else if (v == 2) return getYA(cellular_automata_space, x, y, z);
	else if (v == 3) return getYB(cellular_automata_space, x, y, z);
	else if (v == 4) return getZA(cellular_automata_space, x, y, z);
	return getZB(cellular_automata_space, x, y, z);
}

std::vector<unsigned int> HexagonalNeighborhood::getXA(const std::shared_ptr< CellularAutomataSpace > & cellular_automata_space, unsigned int x, unsigned int y, unsigned int z) const
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
		for (int j = -radius; j <= radius; j++)
		{
			if (((i != -1) || (j != -1)) && ((i != 1) || (j != 1)))
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
					if (cellular_automata_space->getCells()[current_x][current_y][current_z] != 0)
					{
						neighborhood.push_back(cellular_automata_space->getCells()[current_x][current_y][current_z]);
					}
				}
			}
		}
	}
	return neighborhood;
}

std::vector<unsigned int> HexagonalNeighborhood::getXB(const std::shared_ptr< CellularAutomataSpace > & cellular_automata_space, unsigned int x, unsigned int y, unsigned int z)const
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
		for (int j = -radius; j <= radius; j++)
		{
			if (((i != -1) || (j != 1)) && ((i != 1) || (j != -1)))
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
					if (cellular_automata_space->getCells()[current_x][current_y][current_z] != 0)
					{
						neighborhood.push_back(cellular_automata_space->getCells()[current_x][current_y][current_z]);
					}
				}
			}
		}
	}
	return neighborhood;
}
																																												
std::vector<unsigned int> HexagonalNeighborhood::getYA(const std::shared_ptr< CellularAutomataSpace > & cellular_automata_space, unsigned int x, unsigned int y, unsigned int z)const
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
			for (int k = -radius; k <= radius; k++)
			{
				if (((i != -1) || (k != -1)) && ((i != 1) || (k != 1)))
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
					if (cellular_automata_space->getCells()[current_x][current_y][current_z] != 0)
					{
						neighborhood.push_back(cellular_automata_space->getCells()[current_x][current_y][current_z]);
					}
				}
			}
		}
	}
	return neighborhood;
}
																																												
std::vector<unsigned int> HexagonalNeighborhood::getYB(const std::shared_ptr< CellularAutomataSpace > & cellular_automata_space, unsigned int x, unsigned int y, unsigned int z)const
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
			for (int k = -radius; k <= radius; k++)
			{
				if (((i != 1) || (k != -1)) && ((i != -1) || (k != 1)))
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
					if (cellular_automata_space->getCells()[current_x][current_y][current_z] != 0)
					{
						neighborhood.push_back(cellular_automata_space->getCells()[current_x][current_y][current_z]);
					}
				}
			}
		}
	}
	return neighborhood;
}
																																												
std::vector<unsigned int> HexagonalNeighborhood::getZA(const std::shared_ptr< CellularAutomataSpace > & cellular_automata_space, unsigned int x, unsigned int y, unsigned int z)const
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
			for (int k = -radius; k <= radius; k++)
			{
				if (((j != -1) || (k != -1)) && ((j != 1) || (k != 1)))
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
					if (cellular_automata_space->getCells()[current_x][current_y][current_z] != 0)
					{
						neighborhood.push_back(cellular_automata_space->getCells()[current_x][current_y][current_z]);
					}
				}
			}
		}
	}
	return neighborhood;
}
																																												
std::vector<unsigned int> HexagonalNeighborhood::getZB(const std::shared_ptr< CellularAutomataSpace > & cellular_automata_space, unsigned int x, unsigned int y, unsigned int z)const
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
			for (int k = -radius; k <= radius; k++)
			{
				if (((j != 1) || (k != -1)) && ((j != -1) || (k != 1)))
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
					if (cellular_automata_space->getCells()[current_x][current_y][current_z] != 0)
					{
						neighborhood.push_back(cellular_automata_space->getCells()[current_x][current_y][current_z]);
					}
				}
			}
		}
	}
	return neighborhood;
}