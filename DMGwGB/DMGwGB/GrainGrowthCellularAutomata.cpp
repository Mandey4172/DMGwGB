#include "GrainGrowthCellularAutomata.h"

#include "CellularAutomataSpace.h"
#include "Neighborhood.h"
#include "CellularAutomataRule.h"

#include "MooreNeighborhood.h"
#include "GrainGrowthRule.h"

#include<omp.h>

GrainGrowthCellularAutomata::GrainGrowthCellularAutomata()
{
	cellular_automata_space = std::make_shared< CellularAutomataSpace >(100, 100, 100);
	neighborhood = std::make_shared < MooreNeighborhood >();
	rule = std::make_shared < GrainGrowthRule >();
}

bool GrainGrowthCellularAutomata::step()
{
	std::shared_ptr< CellularAutomataSpace > cellularAutomataSpaceCopy = std::make_shared< CellularAutomataSpace >(*cellular_automata_space);
	int m = static_cast<int>(cellular_automata_space->getSizeOnXAxis()),
		n = static_cast<int>(cellular_automata_space->getSizeOnYAxis()),
		o = static_cast<int>(cellular_automata_space->getSizeOnZAxis());
	bool exit = true;
#pragma omp parallel
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
#pragma omp for schedule(static) nowait
			for (int k = 0; k < o; k++)
			{
				if (cellular_automata_space->getCells()[i][j][k] == 0)
				{
					std::vector<unsigned int> neightborhood = neighborhood->get(cellularAutomataSpaceCopy, i, j, k);
					rule->transition(&cellular_automata_space->getCells()[i][j][k], neightborhood);
					if (cellular_automata_space->getCells()[i][j][k] > 0)
					{
						exit = false;
					}
				}
			}
		}
	}
	return exit;
}