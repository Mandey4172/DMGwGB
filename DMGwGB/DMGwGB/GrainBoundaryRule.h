#pragma once
#include <list>

#include "CRule.h"
#include <omp.h>

struct BoundaryNode
{
	BoundaryNode() {}
	BoundaryNode(const BoundaryNode &obj)
	{
		this->neighborhood_states = obj.neighborhood_states;
		this->state = obj.state;
	}
	//Stany w otoczeniu komórki
	std::vector<unsigned int> neighborhood_states;
	//Stan granicy ziarna
	int state;
};

class GrainBoundaryRule :
	public CRule
{
public:
	GrainBoundaryRule();
	~GrainBoundaryRule();

	std::vector<BoundaryNode> boundary_states;

	virtual void step(unsigned int * cell, class std::vector<unsigned int> & neighborhood);
};

