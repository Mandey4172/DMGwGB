#pragma once
#include "CellularAutomataRule.h"

//Rule for grain growth
class GrainGrowthRule :
	public CellularAutomataRule
{
public:
	void transition(unsigned int * cell, class std::vector<unsigned int > & neighborhood) override;
};
