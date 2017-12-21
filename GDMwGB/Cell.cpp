#include "Cell.h"
#include "SPoint.h"

/*#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>*/     

Cell::Cell()
{
	/* initialize random seed: */
	//srand(time(NULL));
	//this->state = rand() % 3;
	this->state = 0;
	this->fill = 0;
	this->check = false;
	this->position = nullptr;
}


Cell::~Cell()
{
}

void Cell::setState(unsigned int nstate)
{
	this->state = nstate;
}

void Cell::setCheck(bool ncheck)
{
	this->check = ncheck;
}

void Cell::Fill()
{
	this->fill++;
}

unsigned int Cell::getState()
{
	return this->state;
}

bool Cell::Check()
{
	return this->check;
}
