#include "GrainBoundaryRule.h"

#include "Cell.h"

#include <algorithm>    
#include <vector>
#include <omp.h>
bool sortfunction(int i, int j) { return (i<j); }


GrainBoundaryRule::GrainBoundaryRule()
{
}


GrainBoundaryRule::~GrainBoundaryRule()
{
}

void GrainBoundaryRule::step(unsigned int * cell, std::vector<unsigned int> neighborhood)
{
	std::vector<unsigned int> cell_state;


	//unsigned int numberOfBoundarys = 0;
	GNode * nnode = new GNode();

	for (unsigned int n : neighborhood)
	{
		if ((n > 0) && (n <= this->grain_count)) // Dlaczego <= ?? 0 - pusta przestrzen, stany rozpoczynaja sie od 1 i koncza na grain-count.
		{
			bool exist = false;
			for (int s = 0; s < cell_state.size(); ++s)
			{
				if (cell_state[s] == n)
				{
					exist = true;
					break;
				}
			}
			if (!exist)
			{
				cell_state.push_back(n);
			}
		}
		//else if (n > this->grain_count) numberOfBoundarys++;
	}
	std::sort(cell_state.begin(), cell_state.end());
	if (cell_state.size() > 1)
	{
		for (GNode b : this->boundary_states) //Sprawdzanie czy istnieje
		{
			if (b.neighborhood_states.size() == cell_state.size())
			{
				bool exist = true;
				for (int i = 0; i < cell_state.size(); i++)
				{
					if (b.neighborhood_states[i] != cell_state[i])
					{
						exist = false;
						break;
					}
				}
				if (exist && cell)
				{
					*cell = b.state;
					return;
				}
			}
		}
		/*for (int c : cell_state)
		{
			nnode->neighborhood_states.push_back(c);
		}*/
		nnode->neighborhood_states = cell_state;
		nnode->state = this->grain_count + 1 + this->boundary_states.size();
#pragma omp critical
		{
			this->boundary_states.push_back(*nnode);
		}
	}
}

void GrainBoundaryRule::clear(unsigned int * cell, std::vector<unsigned int> neighborhood)
{
	std::vector<unsigned int > cell_state;
	std::vector<unsigned int > cell_state_count;

	unsigned int numberOfBoundarys = 0;
	unsigned int boundarysLinit = neighborhood.size() - static_cast<unsigned int>(std::floor(static_cast<double>(1) / 8 * static_cast<double>(neighborhood.size())));
	for (unsigned int n : neighborhood)
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
	if (numberOfBoundarys > 0 && boundarysLinit <= numberOfBoundarys)
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
