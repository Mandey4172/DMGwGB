#include "GrainBoundarySimulation.h"

#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>

#include "CellularAutomata.h"
#include "Neighborhood.h"
#include "CRule.h"

#include "MooreNeighborhood.h"
#include "VonNeummanNeighborhood.h"
#include "NVonNeummanNeighborhood.h"
#include "GrainBoundaryRule.h"
#include "GrainGrowthSimulation.h"



GrainBoundarySimulation::GrainBoundarySimulation()
{
	this->cellularautomata = new CellularAutomata(50, 50, 50);
	this->neighborhood = new MooreNeighborhood();

	this->rule = new GrainBoundaryRule();
	this->clearIterations = 1;
	this->grainSize = 1;
}


bool GrainBoundarySimulation::step()
{
	bool isComplete = true;

	GrainGrowthSimulation GrainGrowth;
	GrainGrowth.neighborhood = this->neighborhood;
	GrainGrowth.cellularautomata = new CellularAutomata(*this->cellularautomata);
	GrainGrowth.start();

	if (this->cellularautomata) delete this->cellularautomata;
	this->cellularautomata = new CellularAutomata(*GrainGrowth.cellularautomata);
	unsigned int m = this->cellularautomata->getSize()[0],
				 n = this->cellularautomata->getSize()[1],
				 o = this->cellularautomata->getSize()[2];


	GrainGrowthSimulation GrainGrowth2;
	
	GrainGrowth2.cellularautomata = new CellularAutomata(m,n,o);

	this->rule->grain_count = this->cellularautomata->nucleons_count;
	static_cast<GrainBoundaryRule *>(this->rule)->boundary_states.clear();
//	#pragma omp parallel 
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
//			#pragma omp for 
			for (int k = 0; k < o; k++)
			{
				MooreNeighborhood n;
				this->rule->step(&GrainGrowth2.cellularautomata->getCells()[i][j][k], this->neighborhood->get(this->cellularautomata, i, j, k));
				if (GrainGrowth2.cellularautomata->getCells()[i][j][k] > this->cellularautomata->nucleons_count)
				{
					this->cellularautomata->getCells()[i][j][k] = GrainGrowth2.cellularautomata->getCells()[i][j][k];
				}
			}
		}
	}
	GrainGrowth2.cellularautomata->boundarys_count = ((GrainBoundaryRule *)rule)->boundary_states.size();
	GrainGrowth2.neighborhood = this->neighborhood;
	
	if (grainSize > 1)
	{
		for (int i = 1; i < grainSize; i++)
		{
			GrainGrowth2.step();
		}
	}
	for (int i = 0; i < this->cellularautomata->getSize()[0]; i++)
	{
		for (int j = 0; j < this->cellularautomata->getSize()[1]; j++)
		{
			for (int k = 0; k < this->cellularautomata->getSize()[2]; k++)
			{
				if (GrainGrowth2.cellularautomata->getCells()[i][j][k] > this->cellularautomata->nucleons_count)
				{
					this->cellularautomata->getCells()[i][j][k] = GrainGrowth2.cellularautomata->getCells()[i][j][k];
				}
			}
		}
	}

	CellularAutomata* cca = new CellularAutomata(*this->cellularautomata);
	for (int x = 0; x < this->clearIterations; x++)
	{
		for (int i = 0; i < this->cellularautomata->getSize()[0]; i++)
		{
			for (int j = 0; j < this->cellularautomata->getSize()[1]; j++)
			{
				for (int k = 0; k < this->cellularautomata->getSize()[2]; k++)
				{
					static_cast<GrainBoundaryRule *>(this->rule)->clear(&this->cellularautomata->getCells()[i][j][k], this->neighborhood->get(cca, i, j, k));
				}
			}
		}
	}
	delete cca;
	return isComplete;
}

void GrainBoundarySimulation::start()
{
	
	if (this->rule)
		delete this->rule;
	this->rule = new GrainBoundaryRule();
	int state = 0;
	while (!step());
	int stop = 0;
}
