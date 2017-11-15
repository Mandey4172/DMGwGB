#pragma once
#include "CRule.h"
class GrainBoundaryRule :
	public CRule
{
public:
	GrainBoundaryRule();
	~GrainBoundaryRule();

	virtual void step(class Cell * cell, class std::vector<class Cell> neighborhood);
};

