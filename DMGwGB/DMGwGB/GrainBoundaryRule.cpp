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
		if (n > 0 && n <= this->grain_count) // Dlaczego <= ?? Poniewa¿ stany rozpoczynaja sie od 1 i koncza na grain-count.
		{
			bool exist = false;
			/*if (n == 3)
			{
				int x = 10;
			}*/
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
	if (neighborhood.size() == numberOfBoundarys)
	{
		/*int i = rand() % neighborhood.size();
		if (cell)
			*cell = neighborhood[i];*/
		std::vector<unsigned short > n_state;
		std::vector<unsigned short > n_state_count;
		for (unsigned short n : neighborhood)
		{
			bool exist = false;
			for (int i = 0; i < n_state.size() ; i++)
			{
				if (n == n_state[i])
				{
					n_state_count[i]++;
					break;
				}
			}
			if (!exit)
			{
				n_state.push_back(n);
				n_state_count.push_back(1);
			}
			int max = 0;
			if (n_state.size() > 1)
			{
				for (int i = 1; i < n_state.size(); i++)
				{
					if (n_state_count[i] > n_state_count[max])
					{
						max = i;
					}
				}
			}
			*cell = n_state[max];
		}
		return;
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
