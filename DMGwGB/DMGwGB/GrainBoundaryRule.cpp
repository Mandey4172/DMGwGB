#include "GrainBoundaryRule.h"

#include <algorithm>
#include <vector>
#include <omp.h>

void GrainBoundaryRule::transition(unsigned int * cell, std::vector<unsigned int> & neighborhood)
{
	if (!neighborhood.empty())
	{
		std::vector<unsigned int> unique_grains;
		BoundaryNode new_node;
		for (unsigned int n : neighborhood)
		{
			if (n <= grain_count)
			{
				if (std::find(unique_grains.begin(), unique_grains.end(), n) == unique_grains.end())
				{
					unique_grains.push_back(n);
				}
			}
		}
		std::sort(unique_grains.begin(), unique_grains.end());
		bool exist = false;
#pragma omp critical
		{
			if (unique_grains.size() > 1)
			{
				if (!boundary_states.empty())
				{
					for (std::vector<BoundaryNode>::reverse_iterator b = boundary_states.rbegin(); b != boundary_states.rend(); b++)
					{
						if (b->neighborhood_states == unique_grains)
						{
							*cell = b->state;
							exist = true;
						}
					}
				}
				if (!exist)
				{
					new_node.neighborhood_states = unique_grains;
					new_node.state = static_cast<unsigned int>(grain_count + 1 + boundary_states.size());
					*cell = new_node.state;

					boundary_states.push_back(new_node);
				}
			}
		}
	}
}

void GrainBoundaryRule::clear(unsigned int * cell, std::vector<unsigned int>& neighborhood) const
{
	if (!neighborhood.empty())
	{
		std::vector<unsigned int> unique_grains;
		std::vector<unsigned int> count_grain;

		unique_grains.push_back(*cell);
		count_grain.push_back(1);

		for (unsigned int n : neighborhood)
		{
			if (n >= grain_count)
			{
				bool exist = false;
				if (!unique_grains.empty())
				{
					for (unsigned int i = 0; i < unique_grains.size(); i++)
					{
						if (unique_grains.at(i) == n)
						{
							exist = true;
							count_grain.at(i)++;
							break;
						}
					}
				}
				if (!exist)
				{
					unique_grains.push_back(n);
					count_grain.push_back(1);
				}
			}
		}
		if (!unique_grains.empty())
		{
			unsigned int max = 0;
			for (unsigned int i = 1; i < unique_grains.size(); i++)
			{
				if (count_grain.at(max) < count_grain.at(i))
				{
					max = i;
				}
			}
			*cell = unique_grains.at(max);
		}
	}
}