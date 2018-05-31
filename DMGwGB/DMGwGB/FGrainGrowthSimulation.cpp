#include "FGrainGrowthSimulation.h"

#include "CellularAutomata.h"
#include "Neighborhood.h"
#include "CRule.h"

#include <omp.h>

#include "MooreNeighborhood.h"
#include "FGrainGrowthRule.h"


FGrainGrowthSimulation::FGrainGrowthSimulation()
{
	this->cellularautomata = new CellularAutomata(10, 10, 10);
	this->neighborhood = new MooreNeighborhood();
	this->rule = new FGrainGrowthRule();

	unsigned int m = this->cellularautomata->getSize()[0],
		n = this->cellularautomata->getSize()[1],
		o = this->cellularautomata->getSize()[2];

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < o; k++)
			{
				std::array<int, 3> Point = { i,j,k };
				static_cast<FGrainGrowthRule *>(this->rule)->queue.push_back(Point);
			}
		}
	}
}


FGrainGrowthSimulation::~FGrainGrowthSimulation()
{
}

bool FGrainGrowthSimulation::step()
{
	std::list<std::array<int, 3>> TQueue = static_cast<FGrainGrowthRule *>(this->rule)->queue;
	static_cast<FGrainGrowthRule *>(this->rule)->queue.clear();
	
	CellularAutomata * NewCellularAutomata = new CellularAutomata(*this->cellularautomata);

	if (TQueue.size() > 0)
	{
		//#pragma omp parallel
		//#pragma omp single nowait
		{
			for (std::list<std::array<int, 3>>::iterator it = TQueue.begin(); it != TQueue.end(); ++it)
			{
				//#pragma omp task firstprivate(it)
				{
					int thread_count = omp_get_num_threads();
					int thread_num = omp_get_thread_num();
					std::array<int, 3> Point = *it;
					//this->rule->step(&NewCellularAutomata->getCells()[Point[0]][Point[1]][Point[2]], static_cast<MooreNeighborhood *>(this->neighborhood)->fget(this->cellularautomata, Point[0], Point[1], Point[2], static_cast<FGrainGrowthRule *>(this->rule)->queue));
				}
			}
		//#pragma omp taskwait
		}
		
			
		//for (std::array<int, 3> Point : TQueue)
		//{
		//	int x = omp_get_num_threads();
		//	//MooreNeighborhood * n = static_cast<MooreNeighborhood *>(this->neighborhood);
		//	this->rule->step(&NewCellularAutomata->getCells()[Point[0]][Point[1]][Point[2]], static_cast<MooreNeighborhood *>(this->neighborhood)->fget(this->cellularautomata, Point[0], Point[1], Point[2], static_cast<FGrainGrowthRule *>(this->rule)->queue));
		//}
		// Test::: delete this->cellularautomata;
		this->cellularautomata = NewCellularAutomata;
	}
	else
		return true;
	return false;
}

void FGrainGrowthSimulation::start()
{
	int s = 0;
	while (!step());
	int x = 0;
}
