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
	this->cellularautomata = new CellularAutomata(10, 10, 3);
	this->neighborhood = new MooreNeighborhood();
	this->rule = new GrainBoundaryRule();
}


GrainBoundarySimulation::~GrainBoundarySimulation()
{
}

bool GrainBoundarySimulation::step()
{
	bool isComplete = true;

	GrainGrowthSimulation GrainGrowth;
	if (GrainGrowth.cellularautomata)
	{
		delete GrainGrowth.cellularautomata;
	}
	GrainGrowth.neighborhood = this->neighborhood;
	GrainGrowth.cellularautomata = new CellularAutomata(*this->cellularautomata);
	while (!GrainGrowth.step())
	{
		this->cellularautomata = new CellularAutomata(*GrainGrowth.cellularautomata);
	}
	CellularAutomata * newcellularautomata = new CellularAutomata( *this->cellularautomata );

	for (int i = 0; i < this->cellularautomata->getSize()[0]; i++)
	{
		for (int j = 0; j < this->cellularautomata->getSize()[1]; j++)
		{
			for (int k = 0; k < this->cellularautomata->getSize()[2]; k++)
			{
				//MooreNeighborhood n;
				VonNeummanNeighborhood n;
				this->rule->step(&newcellularautomata->getCells()[i][j][k], n.get(this->cellularautomata, i, j, k));
			}
		}
	}
	this->cellularautomata = newcellularautomata;
	for (int i = 0; i < this->cellularautomata->getSize()[0]; i++)
	{
		for (int j = 0; j < this->cellularautomata->getSize()[1]; j++)
		{
			for (int k = 0; k < this->cellularautomata->getSize()[2]; k++)
			{
				NVonNeummanNeighborhood n;
				//VonNeummanNeighborhood n;
				this->rule->step(&newcellularautomata->getCells()[i][j][k], n.get(this->cellularautomata, i, j, k));
			}
		}
	}
	this->cellularautomata = newcellularautomata;

	return isComplete;
}
