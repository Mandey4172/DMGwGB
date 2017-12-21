#include "GrainGrowthRule.h"

#include "Cell.h"

#include <vector>


GrainGrowthRule::GrainGrowthRule()
{
}


GrainGrowthRule::~GrainGrowthRule()
{
}

void GrainGrowthRule::step(Cell * cell, std::vector<class Cell*> neighborhood)
{
	cell->setCheck(false);
	if (cell->getState() > 0)
	{
		for (Cell * n : neighborhood)
		{
			if (n->getState() == 0)
			{
				n->setState(cell->getState());
				n->setCheck(true);
				this->queue->push_back(n);
			}
		}
	}
	else
	{
		cell->setCheck(false);
	}

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
}
