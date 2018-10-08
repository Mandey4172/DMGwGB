#pragma once
#include "CellularAutomataRule.h"

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
	unsigned int state;
};

class GrainBoundaryRuleV2 :
	public CellularAutomataRule
{
public:
	GrainBoundaryRuleV2();
	~GrainBoundaryRuleV2();

	std::vector<BoundaryNode> boundary_states;

	virtual void check(unsigned int * cell, class std::vector<unsigned int> & neighborhood);
	virtual void identify(unsigned int * cell, class std::vector<unsigned int> & neighborhood);
};

