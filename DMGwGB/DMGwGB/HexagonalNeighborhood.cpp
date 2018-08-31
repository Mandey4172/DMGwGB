#include "HexagonalNeighborhood.h"
#include "CellularAutomataSpace.h"


HexagonalNeighborhood::HexagonalNeighborhood()
{
}


HexagonalNeighborhood::~HexagonalNeighborhood()
{
}

std::vector<unsigned int> HexagonalNeighborhood::get(CellularAutomataSpace * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
{
	int v = rand() % 6;
	if (v == 0) return this->getXA(cellularautomata, x, y, z);
	else if (v == 1) return this->getXB(cellularautomata, x, y, z);
	else if (v == 2) return this->getYA(cellularautomata, x, y, z);
	else if (v == 3) return this->getYB(cellularautomata, x, y, z);
	else if (v == 4) return this->getZA(cellularautomata, x, y, z);
	return this->getZB(cellularautomata, x, y, z);
}

std::vector<unsigned int> HexagonalNeighborhood::getXA(CellularAutomataSpace * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
{
	std::vector<unsigned int> neighborhood;
	int m = static_cast<int>(cellularautomata->getSize()[0]),
		n = static_cast<int>(cellularautomata->getSize()[1]),
		o = static_cast<int>(cellularautomata->getSize()[2]);

	for (int i = -radius; i <= radius; i++)
	{
		int current_x = x + i;
		if (cellularautomata->getBoundatyConditionType() == BoundaryContidionTypes::Blocking && ((current_x  < 0)  || (current_x >= m)))
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
		for (int j = -radius; j <= radius; j++)
		{
			if (((i != -1) || (j != -1)) && ((i != 1) || (j != 1)))
			{
				int current_y = y + j;
				if (cellularautomata->getBoundatyConditionType() == BoundaryContidionTypes::Blocking && ((current_y  < 0) || (current_y >= n)))
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
					if (cellularautomata->getCells()[current_x][current_y][current_z] != 0)
					{
						neighborhood.push_back(cellularautomata->getCells()[current_x][current_y][current_z]);
					}
				}
			}
		}
	}
	return neighborhood;
}

std::vector<unsigned int> HexagonalNeighborhood::getXB(CellularAutomataSpace * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
{
	std::vector<unsigned int> neighborhood;
	int m = static_cast<int>(cellularautomata->getSize()[0]),
		n = static_cast<int>(cellularautomata->getSize()[1]),
		o = static_cast<int>(cellularautomata->getSize()[2]);

	for (int i = -radius; i <= radius; i++)
	{
		int current_x = x + i;
		if (cellularautomata->getBoundatyConditionType() == BoundaryContidionTypes::Blocking && ((current_x  < 0) || (current_x  >= m)))
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
		for (int j = -radius; j <= radius; j++)
		{
			if (((i != -1) || (j != 1)) && ((i != 1) || (j != -1)))
			{
				int current_y = y + j;
				if (cellularautomata->getBoundatyConditionType() == BoundaryContidionTypes::Blocking && ((current_y  < 0)  || (current_y >= n)))
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
					if (cellularautomata->getCells()[current_x][current_y][current_z] != 0)
					{
						neighborhood.push_back(cellularautomata->getCells()[current_x][current_y][current_z]);
					}
				}
			}
		}
	}
	return neighborhood;
}

std::vector<unsigned int> HexagonalNeighborhood::getYA(CellularAutomataSpace * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
{
	std::vector<unsigned int> neighborhood;
	int m = static_cast<int>(cellularautomata->getSize()[0]),
		n = static_cast<int>(cellularautomata->getSize()[1]),
		o = static_cast<int>(cellularautomata->getSize()[2]);

	for (int i = -radius; i <= radius; i++)
	{
		int current_x = x + i;
		if (cellularautomata->getBoundatyConditionType() == BoundaryContidionTypes::Blocking && ((current_x  < 0)  || (current_x >= m)))
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
		for (int j = -radius; j <= radius; j++)
		{
			int current_y = y + j;
			if (cellularautomata->getBoundatyConditionType() == BoundaryContidionTypes::Blocking && ((current_y  < 0)  || (current_y >= n)))
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
			for (int k = -radius; k <= radius; k++)
			{
				if (((i != -1) || (k != -1)) && ((i != 1) || (k != 1)))
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
					if (cellularautomata->getCells()[current_x][current_y][current_z] != 0)
					{
						neighborhood.push_back(cellularautomata->getCells()[current_x][current_y][current_z]);
					}
				}
			}
		}
	}
	return neighborhood;
}

std::vector<unsigned int> HexagonalNeighborhood::getYB(CellularAutomataSpace * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
{
	std::vector<unsigned int> neighborhood;
	int m = static_cast<int>(cellularautomata->getSize()[0]),
		n = static_cast<int>(cellularautomata->getSize()[1]),
		o = static_cast<int>(cellularautomata->getSize()[2]);

	for (int i = -radius; i <= radius; i++)
	{
		int current_x = x + i;
		if (cellularautomata->getBoundatyConditionType() == BoundaryContidionTypes::Blocking && ((current_x  < 0)  || (current_x >= m)))
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
		for (int j = -radius; j <= radius; j++)
		{
			int current_y = y + j;
			if (cellularautomata->getBoundatyConditionType() == BoundaryContidionTypes::Blocking && ((current_y  < 0) || (current_y >= n)))
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
			for (int k = -radius; k <= radius; k++)
			{
				if (((i != 1) || (k != -1)) && ((i != -1) || (k != 1)))
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
					if (cellularautomata->getCells()[current_x][current_y][current_z] != 0)
					{
						neighborhood.push_back(cellularautomata->getCells()[current_x][current_y][current_z]);
					}
				}
			}
		}
	}
	return neighborhood;
}

std::vector<unsigned int> HexagonalNeighborhood::getZA(CellularAutomataSpace * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
{
	std::vector<unsigned int> neighborhood;
	int m = static_cast<int>(cellularautomata->getSize()[0]),
		n = static_cast<int>(cellularautomata->getSize()[1]),
		o = static_cast<int>(cellularautomata->getSize()[2]);

	for (int i = -radius; i <= radius; i++)
	{
		int current_x = x + i;
		if (cellularautomata->getBoundatyConditionType() == BoundaryContidionTypes::Blocking && ((current_x  < 0)  || (current_x >= m)))
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
		for (int j = -radius; j <= radius; j++)
		{
			int current_y = y + j;
			if (cellularautomata->getBoundatyConditionType() == BoundaryContidionTypes::Blocking && ((current_y  < 0)  || (current_y >= n)))
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
			for (int k = -radius; k <= radius; k++)
			{
				if (((j != -1) || (k != -1)) && ((j != 1) || (k != 1)))
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
					if (cellularautomata->getCells()[current_x][current_y][current_z] != 0)
					{
						neighborhood.push_back(cellularautomata->getCells()[current_x][current_y][current_z]);
					}
				}
			}
		}
	}
	return neighborhood;
}

std::vector<unsigned int> HexagonalNeighborhood::getZB(CellularAutomataSpace * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
{
	std::vector<unsigned int> neighborhood;
	int m = static_cast<int>(cellularautomata->getSize()[0]),
		n = static_cast<int>(cellularautomata->getSize()[1]),
		o = static_cast<int>(cellularautomata->getSize()[2]);

	for (int i = -radius; i <= radius; i++)
	{
		int current_x = x + i;
		if (cellularautomata->getBoundatyConditionType() == BoundaryContidionTypes::Blocking && ((current_x  < 0)  || (current_x >= m)))
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
		for (int j = -radius; j <= radius; j++)
		{
			int current_y = y + j;
			if (cellularautomata->getBoundatyConditionType() == BoundaryContidionTypes::Blocking && ((current_y  < 0)  || (current_y >= n)))
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
			for (int k = -radius; k <= radius; k++)
			{
				if (((j != 1) || (k != -1)) && ((j != -1) || (k != 1)))
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
					if (cellularautomata->getCells()[current_x][current_y][current_z] != 0)
					{
						neighborhood.push_back(cellularautomata->getCells()[current_x][current_y][current_z]);
					}
				}
			}
		}
	}
	return neighborhood;
}
