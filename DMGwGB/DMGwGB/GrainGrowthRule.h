#pragma once
#include "CellularAutomataRule.h"

//Rule for grain growth
class GrainGrowthRule :
	public CellularAutomataRule
{
public:
	GrainGrowthRule();
	~GrainGrowthRule();

	virtual void transition(unsigned int * cell, class std::vector<unsigned int > & neighborhood) override;
};
