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
		GNode() {}
		GNode(const GNode &obj)
		{
			this->neighborhood_states = obj.neighborhood_states;
			this->state = obj.state;
		}
		std::vector<int> neighborhood_states;
		int state;
	};
	std::vector<GNode> boundary_states;

	virtual void step(unsigned short * cell, class std::vector<unsigned short> neighborhood);
	virtual void clear(unsigned short * cell, class std::vector<unsigned short> neighborhood);
};

