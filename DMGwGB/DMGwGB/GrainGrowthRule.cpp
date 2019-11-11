#include "GrainGrowthRule.h"

#include <vector>

void GrainGrowthRule::transition(unsigned int * cell, std::vector<unsigned int> & neighborhood)
{
	if (!neighborhood.empty())
	{
		std::vector<unsigned int> unique_grains;
		std::vector<unsigned int> count_grain;
		for (unsigned int n : neighborhood)
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