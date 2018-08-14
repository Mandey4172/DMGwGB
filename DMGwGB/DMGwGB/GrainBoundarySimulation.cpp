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
	this->cellularautomata = new CellularAutomata(100, 100, 100);
	this->neighborhood = new MooreNeighborhood();

	this->rule = new GrainBoundaryRule();
	this->clearIterations = 0;
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

	int m = static_cast<int>(cellularautomata->getSize()[0]),
		n = static_cast<int>(cellularautomata->getSize()[1]),
		o = static_cast<int>(cellularautomata->getSize()[2]);

	GrainGrowthSimulation GrainGrowth2;
	GrainGrowth2.cellularautomata = new CellularAutomata(m,n,o);

	
	this->rule->grain_count = this->cellularautomata->nucleons_count;
	#pragma omp parallel 
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			#pragma omp for schedule(static)
			for (int k = 0; k < o; k++)
			{
				MooreNeighborhood n;
				this->rule->step(&GrainGrowth2.cellularautomata->getCells()[i][j][k], this->neighborhood->get(this->cellularautomata, i, j, k));
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
	#pragma omp parallel 
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			#pragma omp for 
			for (int k = 0; k < o; k++)
			{
				if (GrainGrowth2.cellularautomata->getCells()[i][j][k] > 0)
				{
					this->cellularautomata->getCells()[i][j][k] = GrainGrowth2.cellularautomata->getCells()[i][j][k];
				}
			}
		}
	}
	static_cast<GrainBoundaryRule *>(this->rule)->boundary_states.clear();
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
