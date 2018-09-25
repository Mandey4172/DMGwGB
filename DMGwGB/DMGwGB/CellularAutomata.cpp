#include"CellularAutomata.h"
#include"CellularAutomataSpace.h"
#include "CellularAutomataRule.h"
#include"Neighborhood.h"
#include"MooreNeighborhood.h"
#include"VonNeummanNeighborhood.h"
#include"PentagonalNeighborhood.h"
#include"HexagonalNeighborhood.h"

#include<vector>


CellularAutomata::CellularAutomata()
{
	this->cellularautomata = nullptr;
	this->neighborhood = nullptr;
	this->rule = nullptr;
}

CellularAutomata::~CellularAutomata()
{
	/*if (this->cellularautomata) delete cellularautomata;
	if (this->neighborhood) delete this->neighborhood;
	if (this->rule)				delete this->rule;*/
}

bool CellularAutomata::step()
{
	bool isComplete = true;
	return isComplete;
}

void CellularAutomata::start()
{
	while (!step());
}
