#include "CalculationsThread.h"

#include "GrainBoundarySimulation.h"
#include "GrainGrowthSimulation.h"


#include <QDebug.h>
#include <QElapsedTimer.h>

CalculationsThread::CalculationsThread()
{
    this->simulation = new GrainBoundarySimulation();
	//this->simulation = new GrainGrowthSimulation();
	//this->simulation = new FGrainGrowthSimulation();
}


CalculationsThread::~CalculationsThread()
{
    //delete this->simulation;
}

void CalculationsThread::run()
{
	qDebug() << "Calculations Thread : Start - id = " << thread()->currentThreadId() << "/n";
	emit updateDeb(tr("Simulating ..."));
	QElapsedTimer timer;
	timer.start();
    this->simulation->start();
	/*while (!this->simulation->step())
	{
		emit updateVal(this->simulation->cellularautomata);
	}*/
	emit updateVal();
	QString debug = tr("Time : ");
	qDebug() << "Simulation time :" << timer.elapsed() << "milliseconds" << "/n";
	debug += QString::number(timer.elapsed());
	debug += tr(" milliseconds");
	emit updateDeb(debug);
}

