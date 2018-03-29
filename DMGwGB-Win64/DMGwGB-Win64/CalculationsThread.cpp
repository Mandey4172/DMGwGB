#include "CalculationsThread.h"

#include "GrainBoundarySimulation.h"
#include "GrainGrowthSimulation.h"

#include <QDebug.h>

CalculationsThread::CalculationsThread()
{
    //this->simulation = new GrainBoundarySimulation();
	this->simulation = new GrainGrowthSimulation();
}


CalculationsThread::~CalculationsThread()
{
    //delete this->simulation;
}

void CalculationsThread::run()
{
	qDebug() << "Calculations Thread : Start - id = " << thread()->currentThreadId();
    this->simulation->start();
	/*while (!this->simulation->step())
	{
		emit updateVal(this->simulation->cellularautomata);
	}*/
    emit updateVal(this->simulation->cellularautomata);
}
