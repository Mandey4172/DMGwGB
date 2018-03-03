#include "NVonNeummanNeighborhood.h"
#include"CellularAutomata.h"


NVonNeummanNeighborhood::NVonNeummanNeighborhood()
{
}


NVonNeummanNeighborhood::~NVonNeummanNeighborhood()
{
}

//std::vector<class Cell*> NVonNeummanNeighborhood::get(CellularAutomata * cellularautomata, unsigned int x, unsigned int y, unsigned int z)
//{
//	std::vector<Cell*> neighborhood;
//	int m = cellularautomata->getSize()[0],
//		n = cellularautomata->getSize()[1],
//		o = cellularautomata->getSize()[2];
//
//	for (int i = -1; i <= 1; i++)
//	{
//		for (int j = -1; j <= 1; j++)
//		{
//			for (int k = -1; k <= 1; k++)
//			{
//				if ((x + i >= 0) && (x + i < m) && (y + j >= 0) && (y + j < m) && (z + k >= 0) && (z + k < o))
//				{
//					if(i != 0 && j != 0 && k != 0)
//					{
//						if (cellularautomata->getCells()[x + i][y + j][z + k].getState() != 0)
//						neighborhood.push_back(&cellularautomata->getCells()[x + i][y + j][z + k]);
//					}
//				}
//			}
//		}
//	}
//	return neighborhood;
//}
