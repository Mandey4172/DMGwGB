#include "GrainGrowthSimulation.h"

#include "CellularAutomata.h"

#include "Neighborhood.h"
#include"MooreNeighborhood.h"

#include "CRule.h"
#include "GrainGrowthRule.h"




GrainGrowthSimulation::GrainGrowthSimulation()
{
	this->cellularautomata = new CellularAutomata(10, 10, 2);
	this->neighborhood = new MooreNeighborhood();
	this->rule = new GrainGrowthRule();
}

GrainGrowthSimulation::~GrainGrowthSimulation()
{

}

bool GrainGrowthSimulation::step()
{
	bool isComplete = true;
	CellularAutomata * newcellularautomata = new CellularAutomata(this->cellularautomata->getSize()[0], this->cellularautomata->getSize()[1], this->cellularautomata->getSize()[2]);

	for (int i = 0; i < this->cellularautomata->getSize()[0]; i++)
	{
		for (int j = 0; j < this->cellularautomata->getSize()[1]; j++)
		{
			for (int k = 0; k < this->cellularautomata->getSize()[2]; k++)
			{
				if (this->cellularautomata->getCells()[i][j][k].getState() == 0)
				{
					isComplete = false;
					this->rule->step(&newcellularautomata->getCells()[i][j][k], this->neighborhood->get(this->cellularautomata, i, j, k));
				}
				else
					newcellularautomata->getCells()[i][j][k].setState(this->cellularautomata->getCells()[i][j][k].getState());
			}
		}
	}
	this->cellularautomata = newcellularautomata;

	return isComplete;
}
