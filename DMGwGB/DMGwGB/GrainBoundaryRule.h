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
		neighborhood_states = obj.neighborhood_states;
		state = obj.state;
	}
	std::vector<unsigned int> neighborhood_states;
	unsigned int state;
};

//Rule for creating grain boundaries
class GrainBoundaryRule :
	public CellularAutomataRule
{
public:
	GrainBoundaryRule();
	~GrainBoundaryRule();

	std::vector<BoundaryNode> boundary_states;

	/// <summary> Transition function performed on cell. Modyfies cells state to the next time step </summary>
	void transition(unsigned int * cell, class std::vector<unsigned int> & neighborhood) override;
	/// <summary> Clean function performed on cell grid, removing anomalies.</summary>
	virtual void clear(unsigned int * cell, class std::vector<unsigned int> & neighborhood) const;
};
