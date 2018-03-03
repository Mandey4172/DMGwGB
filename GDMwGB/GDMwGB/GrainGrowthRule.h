#pragma once
#include "CRule.h"
class GrainGrowthRule :
	public CRule
{
public:
	GrainGrowthRule();
	~GrainGrowthRule();
	
	virtual void step(unsigned short * cell, class std::vector<unsigned short > neighborhood);
};

