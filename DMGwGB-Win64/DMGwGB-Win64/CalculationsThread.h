#pragma once
#include <QThread.h>

#include "CellularAutomata.h"
#include "CellularAutomataSpace.h"

class CalculationsThread : public QThread
{
	Q_OBJECT

public:
	CalculationsThread();
	~CalculationsThread();

    CellularAutomata * simulation;

private:
	void run() override;

signals:
    void updateVal();
	void updateDeb(const QString text);
};

