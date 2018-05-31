#include "FGrainGrowthRule.h"



FGrainGrowthRule::FGrainGrowthRule()
{
}


FGrainGrowthRule::~FGrainGrowthRule()
{
}

void FGrainGrowthRule::step(unsigned int * cell, std::vector<unsigned int> neighborhood)
{
	if (*cell == 0)
	{
		std::vector<unsigned int> unique_grain;
		std::vector<unsigned int> count_grain;
		//Zliczanie wyst¹pien danego stanu
		for (int n : neighborhood)
		{
			if (n > 0)
			{
				bool exist = false;
				if (!unique_grain.empty())
				{
					for (int i = 0; i < unique_grain.size(); i++)
					{
						if (unique_grain[i] == n)
						{
							exist = true;
							count_grain[i]++;
							break;
						}
					}
				}
				if (!exist)
				{
					unique_grain.push_back(n);
					count_grain.push_back(1);
				}
			}
		}
		//Wybór ziarna
		int max = 0;
		for (int i = 1; i < unique_grain.size(); i++)
		{
			if (count_grain[max] < count_grain[i])
			{
				max = i;
			}
		}
		if (!unique_grain.empty())
		{
			*cell = unique_grain[max];
		}	
	}
}
