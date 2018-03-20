#include "GrainGrowthRule.h"

#include "Cell.h"

#include <vector>


GrainGrowthRule::GrainGrowthRule()
{
}


GrainGrowthRule::~GrainGrowthRule()
{
}

void GrainGrowthRule::step(unsigned short * cell, std::vector<unsigned short> neighborhood)
{
	//if (*cell == 0)
	//{
	//	
	//}
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
		*cell = unique_grain[max];
}


////
	/*for (unsigned int n : cell->neighborhoods)
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
	}*/

	//if (cell->getState() > 0)
	//{
	//	//for (Cell * n : neighborhood)
	//	//{
	//	//	if (n->getState() == 0)
	//	//	{
	//	//		//n->setState(cell->getState());
	//	//		n->neighborhoods.push_back(cell->getState());
	//	//		n->setCheck(true);
	//	//		bool exist = false;
	//	//		for (Cell * c : *this->queue)
	//	//		{
	//	//			if ((c->position.x == n->position.x) && (c->position.y == n->position.y) && (c->position.z == n->position.z))
	//	//			{
	//	//				exist = true;
	//	//			}
	//	//		}
	//	//		if (!exist)
	//	//		{
	//	//			this->queue->push_back(n);
	//	//		}
	//	//	}
	//	//}
	//}
	//
	//if (cell->getState() > 0)
	//{
	//	for (Cell * n : neighborhood)
	//	{
	//		if (n->getState() == 0)
	//		{
	//			//n->setState(cell->getState());
	//			n->neighborhoods.push_back(cell->getState());
	//			n->setCheck(true);
	//			this->queue->push_back(n);
	//		}
	//	}
	//}
	//else
	//{
	//	cell->setCheck(false);
	//}

	/*std::vector<int> cell_state;
	std::vector<int> cell_state_count;*/
	/*for (Cell n : neighborhood)
	{
		if (n.getState() != 0)
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
	if (cell_state_count.size() > 0)
	{
		int max = 0,
		index = 0;
		for (int i = 0; i < cell_state_count.size(); i++)
		{
			if (cell_state_count[i] > max)
			{
				max = cell_state_count[i];
				index = i;
			}
		}
		cell->setState(cell_state[index]);
	}*/
