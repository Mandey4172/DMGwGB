#include "HexagonalNeighborhood.h"
#include "CellularAutomata.h"


HexagonalNeighborhood::HexagonalNeighborhood()
{
}


HexagonalNeighborhood::~HexagonalNeighborhood()
{
}
//
//std::vector<class Cell*> HexagonalNeighborhood::get(CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
//{
//	int v = rand() % 6;
//	if (v == 0) return this->getXA(cellularautomata, x, y, z);
//	else if (v == 1) return this->getXB(cellularautomata, x, y, z);
//	else if (v == 2) return this->getYA(cellularautomata, x, y, z);
//	else if (v == 3) return this->getYB(cellularautomata, x, y, z);
//	else if (v == 4) return this->getZA(cellularautomata, x, y, z);
//	else if (v == 5) return this->getZB(cellularautomata, x, y, z);
//	return std::vector<class Cell*>();
//}
//
//std::vector<class Cell*> HexagonalNeighborhood::getXA(CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
//{
//	std::vector<Cell*> neighborhood;
//	int m = cellularautomata->getSize()[0],
//		n = cellularautomata->getSize()[1],
//		o = cellularautomata->getSize()[2];
//
//	for (int i = -1; i <= 1; i++)
//	{
//		if ((x + i >= 0) && (x + i < m))
//		{
//			for (int j = -1; j <= 1; j++)
//			{
//				if ((y + j >= 0) && (y + j < n))
//				{
//					if (((i != -1) || (j != -1)) && ((i != 1) || (j != 1)))
//					{
//						for (int k = -1; k <= 1; k++)
//						{
//							if ((z + k >= 0) && (z + k < o))
//							{
//								if ((i != 0) || (j != 0) || (k != 0))
//								{
//									if (cellularautomata->getCells()[x + i][y + j][z + k] != 0)
//										neighborhood.push_back(&cellularautomata->getCells()[x + i][y + j][z + k]);
//								}
//							}
//							else
//							{
//								continue;
//							}
//						}
//					}
//				}
//				else
//				{
//					continue;
//				}
//			}
//		}
//		else
//		{
//			continue;
//		}
//	}
//	return neighborhood;
//}
//
//std::vector<class Cell*> HexagonalNeighborhood::getXB(CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
//{
//	std::vector<Cell*> neighborhood;
//	int m = cellularautomata->getSize()[0],
//		n = cellularautomata->getSize()[1],
//		o = cellularautomata->getSize()[2];
//
//	for (int i = -1; i <= 1; i++)
//	{
//		if ((x + i >= 0) && (x + i < m))
//		{
//			for (int j = -1; j <= 1; j++)
//			{
//				if ((y + j >= 0) && (y + j < n))
//				{
//					if (((i != -1) || (j != 1)) && ((i != 1) || (j != -1)))
//					{
//						for (int k = -1; k <= 1; k++)
//						{
//							if ((z + k >= 0) && (z + k < o))
//							{
//								if ((i != 0) || (j != 0) || (k != 0))
//								{
//									if (cellularautomata->getCells()[x + i][y + j][z + k].getState() != 0)
//										neighborhood.push_back(&cellularautomata->getCells()[x + i][y + j][z + k]);
//								}
//							}
//							else
//							{
//								continue;
//							}
//						}
//					}
//				}
//				else
//				{
//					continue;
//				}
//			}
//		}
//		else
//		{
//			continue;
//		}
//	}
//	return neighborhood;
//}
//
//std::vector<class Cell*> HexagonalNeighborhood::getYA(CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
//{
//	std::vector<Cell*> neighborhood;
//	int m = cellularautomata->getSize()[0],
//		n = cellularautomata->getSize()[1],
//		o = cellularautomata->getSize()[2];
//
//	for (int i = -1; i <= 1; i++)
//	{
//		if ((x + i >= 0) && (x + i < m))
//		{
//			for (int j = -1; j <= 1; j++)
//			{
//				if ((y + j >= 0) && (y + j < n))
//				{
//					for (int k = -1; k <= 1; k++)
//					{
//						if ((z + k >= 0) && (z + k < o))
//						{
//							if (((i != -1) || (k != -1)) && ((i != 1) || (k != 1)))
//							{
//								if ((i != 0) || (j != 0) || (k != 0))
//								{
//									if (cellularautomata->getCells()[x + i][y + j][z + k].getState() != 0)
//										neighborhood.push_back(&cellularautomata->getCells()[x + i][y + j][z + k]);
//								}
//							}
//						}
//						else
//						{
//							continue;
//						}
//					}
//				}
//				else
//				{
//					continue;
//				}
//			}
//		}
//		else
//		{
//			continue;
//		}
//	}
//	return neighborhood;
//}
//
//std::vector<class Cell*> HexagonalNeighborhood::getYB(CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
//{
//	std::vector<Cell*> neighborhood;
//	int m = cellularautomata->getSize()[0],
//		n = cellularautomata->getSize()[1],
//		o = cellularautomata->getSize()[2];
//
//	for (int i = -1; i <= 1; i++)
//	{
//		if ((x + i >= 0) && (x + i < m))
//		{
//			for (int j = -1; j <= 1; j++)
//			{
//				if ((y + j >= 0) && (y + j < n))
//				{
//					for (int k = -1; k <= 1; k++)
//					{
//						if ((z + k >= 0) && (z + k < o))
//						{
//							if (((i != 1) || (k != -1)) && ((i != -1) || (k != 1)))
//							{
//								if ((i != 0) || (j != 0) || (k != 0))
//								{
//									if (cellularautomata->getCells()[x + i][y + j][z + k].getState() != 0)
//										neighborhood.push_back(&cellularautomata->getCells()[x + i][y + j][z + k]);
//								}
//							}
//						}
//						else
//						{
//							continue;
//						}
//					}
//				}
//				else
//				{
//					continue;
//				}
//			}
//		}
//		else
//		{
//			continue;
//		}
//	}
//	return neighborhood;
//}
//
//std::vector<class Cell*> HexagonalNeighborhood::getZA(CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
//{
//	std::vector<Cell*> neighborhood;
//	int m = cellularautomata->getSize()[0],
//		n = cellularautomata->getSize()[1],
//		o = cellularautomata->getSize()[2];
//
//	for (int i = -1; i <= 1; i++)
//	{
//		if ((x + i >= 0) && (x + i < m))
//		{
//			for (int j = -1; j <= 1; j++)
//			{
//				if ((y + j >= 0) && (y + j < n))
//				{
//					for (int k = -1; k <= 1; k++)
//					{
//						if ((z + k >= 0) && (z + k < o))
//						{
//							if (((j != -1) || (k != -1)) && ((j != 1) || (k != 1)))
//							{
//								if ((i != 0) || (j != 0) || (k != 0))
//								{
//									if (cellularautomata->getCells()[x + i][y + j][z + k].getState() != 0)
//										neighborhood.push_back(&cellularautomata->getCells()[x + i][y + j][z + k]);
//								}
//							}
//						}
//						else
//						{
//							continue;
//						}
//					}
//				}
//				else
//				{
//					continue;
//				}
//			}
//		}
//		else
//		{
//			continue;
//		}
//	}
//	return neighborhood;
//}
//
//std::vector<class Cell*> HexagonalNeighborhood::getZB(CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
//{
//	std::vector<Cell*> neighborhood;
//	int m = cellularautomata->getSize()[0],
//		n = cellularautomata->getSize()[1],
//		o = cellularautomata->getSize()[2];
//
//	for (int i = -1; i <= 1; i++)
//	{
//		if ((x + i >= 0) && (x + i < m))
//		{
//			for (int j = -1; j <= 1; j++)
//			{
//				if ((y + j >= 0) && (y + j < n))
//				{
//					for (int k = -1; k <= 1; k++)
//					{
//						if ((z + k >= 0) && (z + k < o))
//						{
//							if (((j != 1) || (k != -1)) && ((j != -1) || (k != 1)))
//							{
//								if ((i != 0) || (j != 0) || (k != 0))
//								{
//									if (cellularautomata->getCells()[x + i][y + j][z + k].getState() != 0)
//										neighborhood.push_back(&cellularautomata->getCells()[x + i][y + j][z + k]);
//								}
//							}
//						}
//						else
//						{
//							continue;
//						}
//					}
//				}
//				else
//				{
//					continue;
//				}
//			}
//		}
//		else
//		{
//			continue;
//		}
//	}
//	return neighborhood;
//}
