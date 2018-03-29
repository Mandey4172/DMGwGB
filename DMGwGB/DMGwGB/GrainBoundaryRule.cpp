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

	//unsigned int numberOfBoundarys = 0;
	GNode * nnode = new GNode();

	for (unsigned short n : neighborhood)
	{
		if (n > 0 && n <= this->grain_count) // Dlaczego <= ?? Poniewa¿ stany rozpoczynaja sie od 1 i koncza na grain-count.
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
		//else if (n > this->grain_count) numberOfBoundarys++;
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
				if (exist && cell)
				{
					*cell = b.state;
					return;
				}
			}
		}
		for (int c : cell_state)
		{
			nnode->neighborhood_states.push_back(c);
		}

		nnode->state = this->grain_count + 1 + this->boundary_states.size();
		int xa = this->boundary_states.max_size();
#pragma omp critical
		{
			this->boundary_states.push_back(*nnode);
		}
		*cell = nnode->state;
	}
}

void GrainBoundaryRule::clear(unsigned short * cell, std::vector<unsigned short> neighborhood)
{
	std::vector<unsigned short > cell_state;
	std::vector<unsigned short > cell_state_count;

	unsigned int numberOfBoundarys = 0;

	for (unsigned short n : neighborhood)
	{
		if (n > this->grain_count) // Dlaczego <= ?? Poniewa¿ stany rozpoczynaja sie od 1 i koncza na grain-count.
		{
			numberOfBoundarys++;
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
	}
	if (numberOfBoundarys > 0 && neighborhood.size() == numberOfBoundarys)
	{
		int max = 0;
		for (int i = 0; i < cell_state_count.size(); i++)
		{
			if (cell_state_count[i] > cell_state_count[max])
				max = i;
		}
		*cell = cell_state[max];
	}
}
