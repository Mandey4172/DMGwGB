#pragma once

#include "CellularAutomataRule.h"
#include <omp.h>

struct BoundaryNode
{
	BoundaryNode() 
	{
		state = 0;
	}
	BoundaryNode(const BoundaryNode &obj)
	{
		this->neighborhood_states = obj.neighborhood_states;
		this->state = obj.state;
	}
	//Stany w otoczeniu komórki
	std::vector<unsigned int> neighborhood_states;
	//Stan granicy ziarna
	unsigned int state;
};

class GrainBoundaryRule :
	public CellularAutomataRule
{
public:
	GrainBoundaryRule();
	~GrainBoundaryRule();

	std::vector<BoundaryNode> boundary_states;

	virtual void check(unsigned int * cell, class std::vector<unsigned int> & neighborhood);
	virtual void clear(unsigned int * cell, class std::vector<unsigned int> & neighborhood);
};

