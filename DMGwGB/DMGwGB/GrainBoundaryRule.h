#pragma once

#include "CellularAutomataRule.h"
#include <omp.h>

struct BoundaryNode
{
	std::vector<unsigned int> neighborhood_states;
	unsigned int state = 0;
};

//Rule for creating grain boundaries
class GrainBoundaryRule :
	public CellularAutomataRule
{
public:
	std::vector<BoundaryNode> boundary_states;

	/// <summary> Transition function performed on cell. Modyfies cells state to the next time step </summary>
	void transition(unsigned int * cell, class std::vector<unsigned int> & neighborhood) override;
	/// <summary> Clean function performed on cell grid, removing anomalies.</summary>
	void clear(unsigned int * cell, class std::vector<unsigned int> & neighborhood) const;
};
