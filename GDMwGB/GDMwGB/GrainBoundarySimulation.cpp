#include "GrainBoundarySimulation.h"

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
	this->neighborhoodGrainBoundary = new MooreNeighborhood();
	this->rule = new GrainBoundaryRule();

	this->grainSize = 1;
}


bool GrainBoundarySimulation::step()
{
	

	bool isComplete = true;

	GrainGrowthSimulation GrainGrowth;
	GrainGrowth.neighborhood = this->neighborhood;

	GrainGrowth.cellularautomata = new CellularAutomata(*this->cellularautomata);
	
	
	/*while (!GrainGrowth.step())
	{
		GDMwGB::MyForm::mut->WaitOne();
		this->cellularautomata = new CellularAutomata(*GrainGrowth.cellularautomata);
		GDMwGB::MyForm::mut->ReleaseMutex();
	}*/
	GrainGrowth.start();
	this->cellularautomata = new CellularAutomata(*GrainGrowth.cellularautomata);
	CellularAutomata * newcellularautomata = new CellularAutomata( *this->cellularautomata );

	GrainGrowthSimulation GrainGrowth2;

	GrainGrowth2.cellularautomata = new CellularAutomata(	newcellularautomata->getSize()[0],
															newcellularautomata->getSize()[1],
															newcellularautomata->getSize()[2]);

	this->rule->grain_count = this->cellularautomata->nucleons_count;
	for (int i = 0; i < this->cellularautomata->getSize()[0]; i++)
	{
		for (int j = 0; j < this->cellularautomata->getSize()[1]; j++)
		{
			for (int k = 0; k < this->cellularautomata->getSize()[2]; k++)
			{
				MooreNeighborhood n;
				this->rule->step(&this->cellularautomata->getCells()[i][j][k], n.get(this->cellularautomata, i, j, k));
				if (this->cellularautomata->getCells()[i][j][k] > this->cellularautomata->nucleons_count)
				{
					GrainGrowth2.cellularautomata->getCells()[i][j][k] = this->cellularautomata->getCells()[i][j][k];
				}
			}
		}
	}
	GrainGrowth2.cellularautomata->boundarys_count = ((GrainBoundaryRule *)rule)->boundary_states.size();
	GrainGrowth2.neighborhood = this->neighborhoodGrainBoundary;
	
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
	
	return isComplete;
}

void GrainBoundarySimulation::start()
{
	int state = 0;
	if (this->rule)
		delete this->rule;
	this->rule = new GrainBoundaryRule();
	while (!step());
	int stop = 0;
}
