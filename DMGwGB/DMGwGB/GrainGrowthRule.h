#pragma once
#include "CellularAutomataRule.h"

class GrainGrowthRule :
	public CellularAutomataRule
{
public:
	GrainGrowthRule();
	~GrainGrowthRule();

	virtual void check(unsigned int * cell, class std::vector<unsigned int > & neighborhood);
};
