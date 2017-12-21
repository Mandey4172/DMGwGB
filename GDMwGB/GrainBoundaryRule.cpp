#include "GrainBoundaryRule.h"

#include "Cell.h"

#include <algorithm>    
#include <vector>

bool sortfunction(int i, int j) { return (i<j); }

GrainBoundaryRule::GrainBoundaryRule()
{
}


GrainBoundaryRule::~GrainBoundaryRule()
{
}

void GrainBoundaryRule::step(Cell * cell, std::vector<Cell*> neighborhood)
{
	std::vector<int> cell_state;
	std::vector<int> cell_state_count;
	for (Cell * n : neighborhood)
	{
		if (n->getState() > 1)
		{
			bool exist = false;
			for (int s = 0; s < cell_state.size(); ++s)
			{
				if (cell_state[s] == n->getState())
				{
					cell_state_count[s]++;
					exist = true;
				}
			}
			if (!exist)
			{
				cell_state.push_back(n->getState());
				cell_state_count.push_back(1);
			}
		}
		
	}
	std::sort(cell_state.begin(), cell_state.end());
	if (cell_state.size() > 1)
	{
		for (GNode b : this->boundary_states)
		{
			if (b.neighborhood_states.size() == cell_state.size())
			{
				bool exist = true;
				for (int i = 0; i < cell_state.size(); i++)
				{
					if (b.neighborhood_states[i] != cell_state[i])
					{
						exist = false;
					}
				}
				if (exist)
				{
					cell->setState(b.state);
					return;
				}
			}
		}
		GNode nnode;
		for (int c : cell_state)
		{
			nnode.neighborhood_states.push_back(c);
		}
		nnode.state = this->grain_count + this->boundary_states.size();
		cell->setState(nnode.state);
		this->boundary_states.push_back(nnode);
	}
}
