#include "Calculations.h"


Calculations::Calculations()
{
}

Calculations::~Calculations()
{
	if (this->simulation) delete simulation;
}

void Calculations::simulate()
{
	this->simulation->start();
}
