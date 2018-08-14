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
	#pragma omp parallel
	for (int i = 0; i < m; i++)
	{
		int x = 0;
		for (int j = 0; j < n; j++)
		{
			#pragma omp for schedule(dynamic)
			for (int k = 0; k < o; k++)
			{
				if(this->cellularautomata->getCells()[i][j][k] == 0)
				{
					this->rule->step(&this->cellularautomata->getCells()[i][j][k], this->neighborhood->get(cca, i, j, k));
					exit = false;
				}
			}
		}
	}
	delete cca;

	return exit;
}

void GrainGrowthSimulation::start()
{
	int m = static_cast<int>(cellularautomata->getSize()[0]),
		n = static_cast<int>(cellularautomata->getSize()[1]),
		o = static_cast<int>(cellularautomata->getSize()[2]);

	while (!step());
}
