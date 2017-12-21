#pragma once
#include "CRule.h"
class GrainGrowthRule :
	public CRule
{
public:
	GrainGrowthRule();
	~GrainGrowthRule();
	
	virtual void step(class Cell * cell, class std::vector<class Cell*> neighborhood);
	std::vector<class Cell *> * queue;
};

