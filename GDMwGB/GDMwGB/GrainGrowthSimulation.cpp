#include "GrainGrowthSimulation.h"

#include "CellularAutomata.h"
#include "Neighborhood.h"
#include "CRule.h"
#include "SPoint.h"

#include "MooreNeighborhood.h"
#include "GrainGrowthRule.h"

#include<omp.h>


GrainGrowthSimulation::GrainGrowthSimulation()
{
	this->cellularautomata = new CellularAutomata(10, 10, 10);
	this->neighborhood = new MooreNeighborhood();
	this->rule = new GrainGrowthRule();
	for (int i = 0; i < this->cellularautomata->getSize()[0]; i++)
	{
		for (int j = 0; j < this->cellularautomata->getSize()[1]; j++)
		{
			for (int k = 0; k < this->cellularautomata->getSize()[2]; k++)
			{
				//this->queue.push_back(&this->cellularautomata->getCells()[i][j][k]);
			}
		}
	}
	
}

GrainGrowthSimulation::~GrainGrowthSimulation()
{

}

bool GrainGrowthSimulation::step()
{
	omp_set_num_threads(4);
	bool exit = true;
	CellularAutomata cca = CellularAutomata(*this->cellularautomata);
	#pragma omp parallel for num_threads(4)
	for (int i = 0; i < this->cellularautomata->getSize()[0]; i++)
	{
		int tid = omp_get_thread_num();
		for (int j = 0; j < this->cellularautomata->getSize()[1]; j++)
		{
			for (int k = 0; k < this->cellularautomata->getSize()[2]; k++)
			{
				
				this->rule->step(&this->cellularautomata->getCells()[i][j][k], this->neighborhood->get(&cca, i, j, k));
				if (this->cellularautomata->getCells()[i][j][k] != cca.getCells()[i][j][k]) exit = false;
			}
		}
	}
	return exit;
}

void GrainGrowthSimulation::start()
{
	//this->queue.clear();
	//for (int  i= 0; i < this->cellularautomata->getSize()[0]; i++)
	//{
	//	for (int j = 0; j < this->cellularautomata->getSize()[1]; j++)
	//	{
	//		for (int k = 0; k< this->cellularautomata->getSize()[2]; k++)
	//		{
	//			//this->cellularautomata->getCells()[i][j][k].setCheck(true);
	//			//this->queue.push_back(&this->cellularautomata->getCells()[i][j][k]);
	//		}
	//	}
	//}
	int start = 0;
	while (!step());
	int stop = 0;
}
