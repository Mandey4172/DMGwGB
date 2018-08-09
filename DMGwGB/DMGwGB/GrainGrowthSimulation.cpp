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
	//new VonNeummanNeighborhood();
	//new HexagonalNeighborhood();
	//new PentagonalNeighborhood();
	this->rule = new GrainGrowthRule();
}

GrainGrowthSimulation::~GrainGrowthSimulation()
{

}

bool GrainGrowthSimulation::step()
{
	CellularAutomata * cca = new CellularAutomata(*this->cellularautomata);

	int m = static_cast<int>(cellularautomata->getSize()[0]),
		n = static_cast<int>(cellularautomata->getSize()[1]),
		o = static_cast<int>(cellularautomata->getSize()[2]);

	bool exit = true;
	//pragma omp parallel num_threads(4) 
	#pragma omp parallel
	for (int i = 0; i < m; i++)
	{
		int x = 0;
		for (int j = 0; j < n; j++)
		{
			#pragma omp for schedule(dynamic)
			for (int k = 0; k < o; k++)
			{
				//if (cca->getCells()[i][j][k] == 0)
				if (this->cellularautomata->front[i][j][k])
				{
					//cca->front[i][j][k] = false;
					//int thread_count = omp_get_num_threads();
					//int thread_num = omp_get_thread_num();
					this->rule->step(&this->cellularautomata->getCells()[i][j][k], this->neighborhood->get(cca, i, j, k));
					if (this->cellularautomata->getCells()[i][j][k] > 0)
					{
						exit = false;
					}
				}
			}
		}
	}
	bool *** swap = this->cellularautomata->front;
	this->cellularautomata->front = cca->front;
	cca->front = swap;

	delete cca;

	return exit;
}

void GrainGrowthSimulation::start()
{
	//Lokalna kopi przyspiesza kod
	int m = static_cast<int>(cellularautomata->getSize()[0]),
		n = static_cast<int>(cellularautomata->getSize()[1]),
		o = static_cast<int>(cellularautomata->getSize()[2]);

	for (int  i= 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < o; k++)
			{
				if (this->cellularautomata->getCells()[i][j][k] > 0)
				{
					this->cellularautomata->front[i][j][k] = true;
				}
			}
		}
	}
	int xa = 500;
	int start = 0;
	while (!step());
	int stop = 0;
}
