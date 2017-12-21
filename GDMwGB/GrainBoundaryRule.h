#pragma once
#include "CRule.h"
class GrainBoundaryRule :
	public CRule
{
public:
	GrainBoundaryRule();
	~GrainBoundaryRule();

	struct GNode
	{
		std::vector<int> neighborhood_states;
		int state;
	};
	std::vector<GNode> boundary_states;

	virtual void step(class Cell * cell, class std::vector<class Cell*> neighborhood);
};

