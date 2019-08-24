#include "CalculationsThread.h"

#include "GrainGrowthWithBoundaryCellularAutomata.h"
#include "GrainGrowthWithBoundaryCellularAutomataV2.h"
#include "GrainGrowthCellularAutomata.h"


#include <QDebug.h>
#include <QElapsedTimer.h>

CalculationsThread::CalculationsThread()
{
	//simulation = new GrainGrowthCellularAutomata();
    simulation = new GrainGrowthWithBoundaryCellularAutomata();
}


CalculationsThread::~CalculationsThread()
{
    delete simulation;
}

void CalculationsThread::run()
{
	qDebug() << "Calculations Thread : Start - id = " << thread()->currentThreadId() << "/n";
	emit updateDeb(tr("Simulating ..."));
	QElapsedTimer timer;
	timer.start();
    simulation->start();
	/*while (!simulation->step())
	{
		emit updateVal(simulation->cellularautomata);
	}*/
	emit updateVal();
	QString debug = tr("Time : ");
	qDebug() << "Simulation time :" << timer.elapsed() << "milliseconds" << "/n";
	debug += QString::number(timer.elapsed());
	debug += tr(" milliseconds");
	emit updateDeb(debug);
}

