#pragma once
#include <list>

#include "CRule.h"

struct GNode
{
	GNode() {}
	GNode(const GNode &obj)
	{
		this->neighborhood_states = obj.neighborhood_states;
		this->state = obj.state;
	}
	std::vector<unsigned int> neighborhood_states;
	int state;
};

class GrainBoundaryRule :
	public CRule
{
public:
	GrainBoundaryRule();
	~GrainBoundaryRule();

	std::list<GNode> boundary_states;

	virtual void step(unsigned int * cell, class std::vector<unsigned int> neighborhood);
	virtual void clear(unsigned int * cell, class std::vector<unsigned int> neighborhood);
};

