#pragma once
#include <QThread.h>

#include "Simulation.h"
#include "CellularAutomata.h"

class CalculationsThread : public QThread
{
	Q_OBJECT

public:
	CalculationsThread();
	~CalculationsThread();

    Simulation * simulation;

private:
	void run() override;

signals:
    void updateVal();
	void updateDeb(const QString text);
};

