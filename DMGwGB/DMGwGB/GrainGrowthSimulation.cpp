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
}

GrainGrowthSimulation::~GrainGrowthSimulation()
{

}

bool GrainGrowthSimulation::step()
{
	bool exit = true;
	CellularAutomata cca = *this->cellularautomata;
	//#pragma omp parallel num_threads(4) 
	#pragma omp parallel
	for (int i = 0; i < this->cellularautomata->getSize()[0]; i++)
	{
		for (int j = 0; j < this->cellularautomata->getSize()[1]; j++)
		{
			#pragma omp for 
			for (int k = 0; k < this->cellularautomata->getSize()[2]; k++)
			{
				if (this->cellularautomata->getCells()[i][j][k] == 0 && this->cellularautomata->front[i][j][k])
				{
					this->rule->step(&this->cellularautomata->getCells()[i][j][k], this->neighborhood->get(&cca, i, j, k));
					if (this->cellularautomata->getCells()[i][j][k] != 0)
					{
						//int val = this->cellularautomata->getCells()[i][j][k];
						exit = false;
					}
				}
			}
		}
	}
	
	this->cellularautomata->front = cca.front;
	return exit;
}

void GrainGrowthSimulation::start()
{
	//this->queue.clear();
	for (int  i= 0; i < this->cellularautomata->getSize()[0]; i++)
	{
		for (int j = 0; j < this->cellularautomata->getSize()[1]; j++)
		{
			for (int k = 0; k< this->cellularautomata->getSize()[2]; k++)
			{
				//this->cellularautomata->getCells()[i][j][k].setCheck(true);
				//this->queue.push_back(&this->cellularautomata->getCells()[i][j][k]);
				this->cellularautomata->front[i][j][k] = true;
			}
		}
	}
	int start = 0;
	while (!step());
	int stop = 0;
}
