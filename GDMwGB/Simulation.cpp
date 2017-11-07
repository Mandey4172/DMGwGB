#include "Simulation.h"
#include<vector>
#include"CellularAutomata.h"
#include"CRule.h"
#include"Neighborhood.h"
#include"MooreNeighborhood.h"
#include"VonNeummanNeighborhood.h"
#include"PentagonalNeighborhood.h"
#include"HexagonalNeighborhood.h"

Simulation::Simulation()
{
	int x = 10;
	this->cellularautomata = new CellularAutomata(x, x, x);
	this->neighborhood = new HexagonalNeighborhood();
	this->rule = new CRule();
	/*this->cellularautomata->getCells()[rand() % 10][rand() % 10][rand() % 10].setState(1);*/
	this->cellularautomata->getCells()[x / 2][x / 2][0].setState(1);
	this->cellularautomata->getCells()[x-1][x/2][x/2].setState(2);
}

void Simulation::step()
{
	CellularAutomata * newcellularautomata = new CellularAutomata(this->cellularautomata->getSize()[0], this->cellularautomata->getSize()[1], this->cellularautomata->getSize()[2]);
	
	for (int i = 0 ; i < this->cellularautomata->getSize()[0]; i++)
	{
		for (int j = 0; j < this->cellularautomata->getSize()[1]; j++)
		{
			for (int k = 0; k < this->cellularautomata->getSize()[2]; k++)
			{
				if (this->cellularautomata->getCells()[i][j][k].getState() == 0)
					this->rule->step(&newcellularautomata->getCells()[i][j][k], this->neighborhood->get(this->cellularautomata, i, j, k));
				else
					newcellularautomata->getCells()[i][j][k].setState(this->cellularautomata->getCells()[i][j][k].getState());
			}
		}
	}
	this->cellularautomata = newcellularautomata;
	//throw gcnew System::NotImplementedException();
}
