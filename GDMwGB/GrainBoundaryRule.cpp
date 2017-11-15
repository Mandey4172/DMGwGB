#include "GrainBoundaryRule.h"

#include "Cell.h"

#include <vector>

GrainBoundaryRule::GrainBoundaryRule()
{
}


GrainBoundaryRule::~GrainBoundaryRule()
{
}

void GrainBoundaryRule::step(Cell * cell, std::vector<Cell> neighborhood)
{
	std::vector<int> cell_state;
	std::vector<int> cell_state_count;
	for (Cell n : neighborhood)
	{
		if (n.getState() > 1)
		{
			bool exist = false;
			for (int s = 0; s < cell_state.size(); ++s)
			{
				if (cell_state[s] == n.getState())
				{
					cell_state_count[s]++;
					exist = true;
				}
			}
			if (!exist)
			{
				cell_state.push_back(n.getState());
				cell_state_count.push_back(1);
			}
		}
		
	}
	if (cell_state.size() > 1)
	{
		cell->setState(1);
	}
}
