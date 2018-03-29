#include "FGrainGrowthSimulation.h"

#include "CellularAutomata.h"
#include "Neighborhood.h"
#include "CRule.h"


#include "MooreNeighborhood.h"
#include "FGrainGrowthRule.h"


FGrainGrowthSimulation::FGrainGrowthSimulation()
{
	this->cellularautomata = new CellularAutomata(10, 10, 10);
	this->neighborhood = new MooreNeighborhood();
	this->rule = new FGrainGrowthRule();
	for (int i = 0; i < this->cellularautomata->getSize()[0]; i++)
	{
		for (int j = 0; j < this->cellularautomata->getSize()[1]; j++)
		{
			for (int k = 0; k < this->cellularautomata->getSize()[2]; k++)
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
	std::vector<std::array<int, 3>> TQueue = static_cast<FGrainGrowthRule *>(this->rule)->queue;
	static_cast<FGrainGrowthRule *>(this->rule)->queue.clear();
	
	CellularAutomata * NewCellularAutomata = new CellularAutomata(*this->cellularautomata);
	
	if (TQueue.size() > 0)
	{
		for (std::array<int, 3> Point : TQueue)
		{
			//this->rule->step(&NewCellularAutomata->getCells()[Point[0]][Point[1]][Point[2]],this->neighborhood->fget(this->cellularautomata,Point[0],Point[1],Point[2], static_cast<FGrainGrowthRule *>(this->rule)->queue));
		}
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
