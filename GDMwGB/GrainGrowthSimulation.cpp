#include "GrainGrowthSimulation.h"

#include "CellularAutomata.h"

#include "Neighborhood.h"
#include "MooreNeighborhood.h"

#include "CRule.h"
#include "GrainGrowthRule.h"

#include "SPoint.h"

#include "MainForm.h"


GrainGrowthSimulation::GrainGrowthSimulation()
{
	this->cellularautomata = new CellularAutomata(10, 10, 10);
	this->neighborhood = new MooreNeighborhood();
	this->rule = new GrainGrowthRule();
	for (int i = 0; i < this->cellularautomata->getSize()[0]; i++)
	{
		for (int j = 0; j < this->cellularautomata->getSize()[1]; j++)
		{
			for (int k = 0; k < this->cellularautomata->getSize()[2]; k++)
			{
				this->queue.push_back(&this->cellularautomata->getCells()[i][j][k]);
			}
		}
	}
	((GrainGrowthRule *)this->rule)->queue = &this->queue;
}

GrainGrowthSimulation::~GrainGrowthSimulation()
{

}

bool GrainGrowthSimulation::step()
{
	//GDMwGB::MyForm::mut->WaitOne();
	CellularAutomata * newcellularautomata = new CellularAutomata(*this->cellularautomata);
	//GDMwGB::MyForm::mut->ReleaseMutex();

	if (this->queue.size() == 0) return true;
	std::vector<class Cell *> * aqueue = new std::vector<class Cell *>(this->queue);
	this->queue.clear();
	for (Cell * p : *aqueue)
	{
		//GDMwGB::MyForm::mut->WaitOne();
		if (p->getState() == 0)
		{
			this->rule->step(&this->cellularautomata->getCells()[p->position.x][p->position.y][p->position.z],
				this->neighborhood->get(newcellularautomata, p->position.x, p->position.y, p->position.z));
		}
		else
		{
			int sad = 2;
		}
		newcellularautomata->getCells()[p->position.x][p->position.y][p->position.z].setState(
			this->cellularautomata->getCells()[p->position.x][p->position.y][p->position.z].getState());

		//GDMwGB::MyForm::mut->ReleaseMutex();
	}
	CellularAutomata * toDelete = this->cellularautomata;

	//GDMwGB::MyForm::mut->WaitOne();
	this->cellularautomata = newcellularautomata;
	//GDMwGB::MyForm::mut->ReleaseMutex();


	delete toDelete;
	delete aqueue;

	return false;
}

void GrainGrowthSimulation::start()
{
	this->queue.clear();
	for (int  i= 0; i < this->cellularautomata->getSize()[0]; i++)
	{
		for (int j = 0; j < this->cellularautomata->getSize()[1]; j++)
		{
			for (int k = 0; k< this->cellularautomata->getSize()[2]; k++)
			{
				this->cellularautomata->getCells()[i][j][k].setCheck(true);
				this->queue.push_back(&this->cellularautomata->getCells()[i][j][k]);
			}
		}
	}
	while (!step());
}
