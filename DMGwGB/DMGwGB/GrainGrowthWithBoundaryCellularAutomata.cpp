#include "GrainGrowthWithBoundaryCellularAutomata.h"

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>

#include "CellularAutomataSpace.h"
#include "Neighborhood.h"
#include "CellularAutomataRule.h"

#include "MooreNeighborhood.h"
#include "VonNeummanNeighborhood.h"
#include "NVonNeummanNeighborhood.h"
#include "GrainBoundaryRule.h"
#include "GrainGrowthCellularAutomata.h"



GrainGrowthWithBoundaryCellularAutomata::GrainGrowthWithBoundaryCellularAutomata()
{
	this->cellularautomata = new CellularAutomataSpace(100, 100, 100);
	this->neighborhood = new MooreNeighborhood();
	this->boundary_neighborhood = new MooreNeighborhood();

	this->rule = new GrainBoundaryRule();
	this->grainSize = 1;
	bFuseAfterSimulation = true;
}


bool GrainGrowthWithBoundaryCellularAutomata::step()
{
	bool isComplete = true;

	GrainGrowthCellularAutomata GrainGrowth;
	GrainGrowth.neighborhood = this->neighborhood;
	GrainGrowth.cellularautomata = this->cellularautomata;
	GrainGrowth.start();

	//this->cellularautomata = new CellularAutomataSpace(*GrainGrowth.cellularautomata);

	int m = static_cast<int>(cellularautomata->getSize()[0]),
		n = static_cast<int>(cellularautomata->getSize()[1]),
		o = static_cast<int>(cellularautomata->getSize()[2]);

	GrainGrowthCellularAutomata GrainGrowth2;
	GrainGrowth2.cellularautomata = new CellularAutomataSpace(m,n,o);
	
	this->rule->grain_count = this->cellularautomata->nucleons_count;

	#pragma omp parallel
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			#pragma omp for schedule(static) nowait
			for (int k = 0; k < o; k++)
			{
				//Pobieranie s¹siedztwa
				MooreNeighborhood n;
				std::vector<unsigned int> neightborhood = n.get(this->cellularautomata, i, j, k);

				this->rule->check(&GrainGrowth2.cellularautomata->getCells()[i][j][k], neightborhood);
			}
		}
	}

	GrainGrowth2.cellularautomata->boundarys_count = static_cast<unsigned int>(((GrainBoundaryRule *)rule)->boundary_states.size());
	GrainGrowth2.neighborhood = this->boundary_neighborhood;
	
	if (grainSize > 1)
	{
		for (unsigned int i = 1; i < grainSize; i++)
		{
			GrainGrowth2.step();
		}
	}
	if (bFuseAfterSimulation)
	{
		#pragma omp parallel 
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				#pragma omp for schedule(static) nowait
				for (int k = 0; k < o; k++)
				{
					if (GrainGrowth2.cellularautomata->getCells()[i][j][k] > 0)
					{
						this->cellularautomata->getCells()[i][j][k] = GrainGrowth2.cellularautomata->getCells()[i][j][k];
					}
				}
			}
		}
	}
	else
		this->cellularautomata = GrainGrowth2.cellularautomata;
	static_cast<GrainBoundaryRule *>(this->rule)->boundary_states.clear();
	return isComplete;
}

void GrainGrowthWithBoundaryCellularAutomata::start()
{
	
	if (this->rule)
		delete this->rule;
	this->rule = new GrainBoundaryRule();
	int state = 0;
	while (!step());
	int stop = 0;
}
