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

void GrainBoundaryRule::step(unsigned short * cell, std::vector<unsigned short> neighborhood)
{
	std::vector<unsigned short > cell_state;
	std::vector<unsigned short > cell_state_count;

	unsigned int numberOfBoundarys = 0;

	for (unsigned short n : neighborhood)
	{
		if (n > 0 && n <= this->grain_count)
		{
			bool exist = false;

			for (int s = 0; s < cell_state.size(); ++s)
			{
				if (cell_state[s] == n)
				{
					cell_state_count[s]++;
					exist = true;
				}
			}
			if (!exist)
			{
				cell_state.push_back(n);
				cell_state_count.push_back(1);
			}
		}
		else if (n > this->grain_count) numberOfBoundarys++;
		
	}
	std::sort(cell_state.begin(), cell_state.end());
	if (neighborhood.size() == numberOfBoundarys)
	{
		int i = rand() % neighborhood.size();
		if (cell)
			*cell = neighborhood[i];
	}
	else if (cell_state.size() > 1)
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
				if (exist && cell)
				{
					*cell = b.state;
					//cell->setState(this->grain_count + 1);
					return;
				}
			}
		}
		GNode nnode;
		for (int c : cell_state)
		{
			nnode.neighborhood_states.push_back(c);
		}
		nnode.state = this->grain_count + 1 + this->boundary_states.size();
		this->boundary_states.push_back(nnode);
		if(cell)
			*cell = nnode.state;
		//cell->setState(this->grain_count + 1);
		
	}
}
