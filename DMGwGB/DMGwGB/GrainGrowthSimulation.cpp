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
	CellularAutomata cca = *this->cellularautomata;
	int n = this->cellularautomata->getSize()[0];
	int m = this->cellularautomata->getSize()[1];
	int	o = this->cellularautomata->getSize()[2];
	bool exit = true;
	//pragma omp parallel num_threads(4) 
	#pragma omp parallel
	for (int i = 0; i < n; i++)
	{
		int x = 0;
		for (int j = 0; j < m; j++)
		{
			#pragma omp for schedule(dynamic)
			for (int k = 0; k < o; k++)
			{
				if (this->cellularautomata->getCells()[i][j][k] == 0 && this->cellularautomata->front[i][j][k])
				{
					this->rule->step(&this->cellularautomata->getCells()[i][j][k], this->neighborhood->get(&cca, i, j, k));
					if (this->cellularautomata->getCells()[i][j][k] != 0)
					{
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
	//Lokalna kopi przyspiesza kod
	int n = this->cellularautomata->getSize()[0],
		m = this->cellularautomata->getSize()[1],
		o = this->cellularautomata->getSize()[2];
	for (int  i= 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < o; k++)
			{
				this->cellularautomata->front[i][j][k] = true;
			}
		}
	}
	int xa = 500;
	int start = 0;
	while (!step());
	int stop = 0;
}
