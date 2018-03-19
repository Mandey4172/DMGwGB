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
	this->check = false;
	this->position = SPoint(0,0,0);
	//this->neighborhoods = std::vector<unsigned int>();
}

Cell::Cell(Cell & c)
{
	this->state = c.state;
	this->position = c.position;
	/*for (unsigned int n : c.neighborhoods)
	{
		this->neighborhoods.push_back(n);
	}*/
}


Cell::~Cell()
{
	//this->neighborhoods.clear();
}

void Cell::setState(unsigned int nstate)
{
	if(this)
		this->state = nstate;
}

void Cell::setCheck(bool ncheck)
{
	this->check = ncheck;
}

unsigned int Cell::getState()
{
	return this->state;
}

bool Cell::Check()
{
	return this->check;
}
