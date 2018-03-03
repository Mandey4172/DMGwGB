#include "Simulation.h"
#include"CellularAutomata.h"
#include"CRule.h"
#include"Neighborhood.h"
#include"MooreNeighborhood.h"
#include"VonNeummanNeighborhood.h"
#include"PentagonalNeighborhood.h"
#include"HexagonalNeighborhood.h"

#include<vector>


Simulation::Simulation()
{

}

Simulation::~Simulation()
{
	if (this->cellularautomata) delete cellularautomata;
	if (this->neighborhood)		delete this->neighborhood;
	if (this->rule)				delete this->rule;
}

bool Simulation::step()
{
	bool isComplete = true;
	return isComplete;
}

void Simulation::start()
{
	while (!step());
}
