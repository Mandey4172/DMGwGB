#include "GrainBoundarySimulation.h"

#include "CellularAutomata.h"
#include "Neighborhood.h"
#include "MooreNeighborhood.h"
#include "VonNeummanNeighborhood.h"
#include "NVonNeummanNeighborhood.h"
#include "CRule.h"
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


GrainBoundarySimulation::~GrainBoundarySimulation()
{
}

bool GrainBoundarySimulation::step()
{
	bool isComplete = true;

	GrainGrowthSimulation GrainGrowth;
	GrainGrowth.neighborhood = this->neighborhood;
	GrainGrowth.cellularautomata = new CellularAutomata(*this->cellularautomata);

	while (!GrainGrowth.step())
	{
		this->cellularautomata = new CellularAutomata(*GrainGrowth.cellularautomata);
	}
	CellularAutomata * newcellularautomata = new CellularAutomata( *this->cellularautomata );
	CellularAutomata * graincellularautomata = new CellularAutomata(	newcellularautomata->getSize()[0], 
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
				this->rule->step(&newcellularautomata->getCells()[i][j][k], n.get(this->cellularautomata, i, j, k));
				if (newcellularautomata->getCells()[i][j][k].getState() > this->cellularautomata->nucleons_count)
				{
					graincellularautomata->getCells()[i][j][k].setState(newcellularautomata->getCells()[i][j][k].getState());
				}
			}
		}
	}
	this->cellularautomata = newcellularautomata;
	this->cellularautomata->boundarys_count = ((GrainBoundaryRule *)rule)->boundary_states.size();

	GrainGrowth.neighborhood = this->neighborhoodGrainBoundary;
	GrainGrowth.cellularautomata = graincellularautomata;

	int k = floor(((float)this->grainSize - 1) / 2);
	for (int i=0 ; i < k ; i++)
	{
		GrainGrowth.step();
	}
	for (int i = 0; i < this->cellularautomata->getSize()[0]; i++)
	{
		for (int j = 0; j < this->cellularautomata->getSize()[1]; j++)
		{
			for (int k = 0; k < this->cellularautomata->getSize()[2]; k++)
			{
				if (GrainGrowth.cellularautomata->getCells()[i][j][k].getState() == 1)
				{
					this->cellularautomata->getCells()[i][j][k].setState(1);
				}
			}
		}
	}

	return isComplete;
}

void GrainBoundarySimulation::start()
{
	for (int i = 0; i < this->cellularautomata->getSize()[0]; i++)
	{
		for (int j = 0; j < this->cellularautomata->getSize()[1]; j++)
		{
			for (int k = 0; k< this->cellularautomata->getSize()[2]; k++)
			{
				this->cellularautomata->getCells()[i][j][k].setCheck(true);
			}
		}
	}
	while (!step());
}
