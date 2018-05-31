#pragma once
#include "CRule.h"
class GrainGrowthRule :
	public CRule
{
public:
	GrainGrowthRule();
	~GrainGrowthRule();
	
	virtual void step(unsigned int * cell, class std::vector<unsigned int > neighborhood);
};

