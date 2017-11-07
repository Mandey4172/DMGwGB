#include "Cell.h"

/*#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>*/     

Cell::Cell()
{
	/* initialize random seed: */
	//srand(time(NULL));
	//this->state = rand() % 3;
	this->state = 0;
}


Cell::~Cell()
{
}

void Cell::setState(unsigned int nstate)
{
	this->state = nstate;
}

unsigned int Cell::getState()
{
	return this->state;
}
