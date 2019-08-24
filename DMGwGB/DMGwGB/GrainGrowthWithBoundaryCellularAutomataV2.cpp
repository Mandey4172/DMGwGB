//#include "GrainGrowthWithBoundaryCellularAutomataV2.h"
//
//#include "CellularAutomataSpace.h"
//#include "MooreNeighborhood.h"
//#include "GrainGrowthCellularAutomata.h"
//
//GrainGrowthWithBoundaryCellularAutomataV2::GrainGrowthWithBoundaryCellularAutomataV2()
//{
//	cellularautomata = new CellularAutomataSpace(100, 100, 100);
//	neighborhood = new MooreNeighborhood();
//	boundary_neighborhood = new MooreNeighborhood();
//
//	rule = new GrainBoundaryRule();
//	grainSize = 1;
//	bFuseAfterSimulation = true;
//}
//
//
//GrainGrowthWithBoundaryCellularAutomataV2::~GrainGrowthWithBoundaryCellularAutomataV2()
//{
//}
//
//bool GrainGrowthWithBoundaryCellularAutomataV2::step()
//{
//	bool isComplete = true;
//
//	GrainGrowthCellularAutomata GrainGrowth;
//	GrainGrowth.neighborhood = neighborhood;
//	GrainGrowth.cellularautomata = cellularautomata;
//	GrainGrowth.start();
//	GrainGrowth.neighborhood = nullptr;
//	GrainGrowth.cellularautomata = nullptr;
//
//	int m = static_cast<int>(cellularautomata->m),
//		n = static_cast<int>(cellularautomata->n),
//		o = static_cast<int>(cellularautomata->o);
//
//	GrainGrowthCellularAutomata GrainGrowth2;
//	GrainGrowth2.cellularautomata = new CellularAutomataSpace(m, n, o);
//
//	rule->grain_count = cellularautomata->nucleons_count;
//
//#pragma omp parallel
//	for (int i = 0; i < m; i++)
//	{
//		for (int j = 0; j < n; j++)
//		{
//#pragma omp for schedule(static) nowait
//			for (int k = 0; k < o; k++)
//			{
//				//Pobieranie s¹siedztwa
//				MooreNeighborhood n;
//				std::vector<unsigned int> neightborhood = n.get(cellularautomata, i, j, k);
//
//				rule->check(&GrainGrowth2.cellularautomata->getCells()[i][j][k], neightborhood);
//			}
//		}
//	}
//
//#pragma omp parallel
//	for (int i = 0; i < m; i++)
//	{
//		for (int j = 0; j < n; j++)
//		{
//#pragma omp for schedule(static) nowait
//			for (int k = 0; k < o; k++)
//			{
//				if (GrainGrowth2.cellularautomata->getCells()[i][j][k] == cellularautomata->nucleons_count + 1)
//				{
//					//Pobieranie s¹siedztwa
//					MooreNeighborhood n;
//					n.setRadius(2);
//					std::vector<unsigned int> neightborhood = n.get(cellularautomata, i, j, k);
//
//					static_cast<GrainBoundaryRuleV2 *>(rule)->identify(&GrainGrowth2.cellularautomata->getCells()[i][j][k], neightborhood);
//				}
//			}
//		}
//	}
//
//	GrainGrowth2.cellularautomata->boundarys_count = static_cast<unsigned int>(((GrainBoundaryRuleV2 *)rule)->boundary_states.size());
//	GrainGrowth2.neighborhood = boundary_neighborhood;
//	if (grainSize > 1)
//	{
//		for (unsigned int i = 1; i < grainSize; i++)
//		{
//			GrainGrowth2.step();
//		}
//	}
//	GrainGrowth2.neighborhood = nullptr;
//
//	if (bFuseAfterSimulation)
//	{
//#pragma omp parallel
//		for (int i = 0; i < m; i++)
//		{
//			for (int j = 0; j < n; j++)
//			{
//#pragma omp for schedule(static) nowait
//				for (int k = 0; k < o; k++)
//				{
//					if (GrainGrowth2.cellularautomata->getCells()[i][j][k] > 0)
//					{
//						cellularautomata->getCells()[i][j][k] = GrainGrowth2.cellularautomata->getCells()[i][j][k];
//					}
//				}
//			}
//		}
//	}
//	else
//	{
//		if (cellularautomata) delete cellularautomata;
//		cellularautomata = GrainGrowth2.cellularautomata;
//		GrainGrowth2.cellularautomata = nullptr;
//	}
//	static_cast<GrainBoundaryRuleV2 *>(rule)->boundary_states.clear();
//	return isComplete;
//}
//
//