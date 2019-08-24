#include "GrainGrowthWithBoundaryCellularAutomata.h"

#include "CellularAutomataSpace.h"
#include "MooreNeighborhood.h"
#include "GrainBoundaryRule.h"
#include "GrainGrowthCellularAutomata.h"

GrainGrowthWithBoundaryCellularAutomata::GrainGrowthWithBoundaryCellularAutomata()
{
	cellular_automata_space = std::make_shared< CellularAutomataSpace >(100, 100, 100);
	neighborhood = std::make_shared < MooreNeighborhood >();
	rule = std::make_shared < GrainBoundaryRule >();
	//? !!!!!!!!!!!
	boundary_neighborhood = std::make_shared< MooreNeighborhood >();

	grainSize = 1;
	bFuseAfterSimulation = true;
}

void GrainGrowthWithBoundaryCellularAutomata::setBoundaryNeighborhood(const std::shared_ptr<class Neighborhood>& new_boundary_neighborhood)
{
	boundary_neighborhood = new_boundary_neighborhood;
}

std::shared_ptr<class Neighborhood> GrainGrowthWithBoundaryCellularAutomata::getBoundaryNeighborhood()
{
	return boundary_neighborhood;
}

bool GrainGrowthWithBoundaryCellularAutomata::step()
{
	bool isComplete = true;

	GrainGrowthCellularAutomata GrainGrowth;
	GrainGrowth.setNeighborhood(neighborhood);
	GrainGrowth.setCellularAutomataSpace(cellular_automata_space);
	GrainGrowth.start();
	GrainGrowth.setNeighborhood(nullptr);
	GrainGrowth.setCellularAutomataSpace(nullptr);

	int m = static_cast<int>(cellular_automata_space->m),
		n = static_cast<int>(cellular_automata_space->n),
		o = static_cast<int>(cellular_automata_space->o);

	GrainGrowthCellularAutomata GrainGrowth2;
	GrainGrowth2.setCellularAutomataSpace(std::make_shared< CellularAutomataSpace >(m, n, o));

	rule->grain_count = cellular_automata_space->nucleons_count;

#pragma omp parallel
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
#pragma omp for schedule(static) nowait
			for (int k = 0; k < o; k++)
			{
				//Pobieranie s¹siedztwa
				MooreNeighborhood n;
				std::vector<unsigned int> neightborhood = n.get(cellular_automata_space, i, j, k);

				rule->check(&GrainGrowth2.getCellularAutomataSpace()->getCells()[i][j][k], neightborhood);
			}
		}
	}
	bool work = true;
	/*for (int x = 0; x < 7; x++)
	{*/

	for (int i = 0; i < m*n*o && work; i++)
	{
		work = false;
		GrainGrowthCellularAutomata GrainGrowth3;
		GrainGrowth3.setCellularAutomataSpace(std::make_shared< CellularAutomataSpace >(*GrainGrowth2.getCellularAutomataSpace()));
#pragma omp parallel
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
#pragma omp for schedule(static) nowait
				for (int k = 0; k < o; k++)
				{
					if (GrainGrowth3.getCellularAutomataSpace()->getCells()[i][j][k] > 0)// cellularautomata->nucleons_count)
					{
						//Pobieranie s¹siedztwa
						MooreNeighborhood n;
						n.setRadius(2);
						std::vector<unsigned int> neightborhood = n.get(GrainGrowth3.getCellularAutomataSpace(), i, j, k);

						static_cast<GrainBoundaryRule *>(rule.get())->clear(&GrainGrowth2.getCellularAutomataSpace()->getCells()[i][j][k], neightborhood);
						if (GrainGrowth2.getCellularAutomataSpace()->getCells()[i][j][k] != GrainGrowth3.getCellularAutomataSpace()->getCells()[i][j][k])
						{
							work = true;
						}
					}
				}
			}
		}
	}

	GrainGrowth2.getCellularAutomataSpace()->boundarys_count = static_cast<unsigned int>(((GrainBoundaryRule *)rule.get())->boundary_states.size());
	GrainGrowth2.setNeighborhood(boundary_neighborhood);
	if (grainSize > 1)
	{
		for (unsigned int i = 1; i < grainSize; i++)
		{
			GrainGrowth2.step();
		}
	}
	GrainGrowth2.setNeighborhood(nullptr);

	if (bFuseAfterSimulation)
	{
#pragma omp parallel
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
#pragma omp for schedule(static) nowait
				for (int k = 0; k < o; k++)
				{
					if (GrainGrowth2.getCellularAutomataSpace()->getCells()[i][j][k] > 0)
					{
						getCellularAutomataSpace()->getCells()[i][j][k] = GrainGrowth2.getCellularAutomataSpace()->getCells()[i][j][k];
					}
				}
			}
		}
	}
	else
	{
		//if (cellular_automata_space) delete cellular_automata_space;
		setCellularAutomataSpace(GrainGrowth2.getCellularAutomataSpace());
		GrainGrowth2.setCellularAutomataSpace(nullptr);
	}

	static_cast<GrainBoundaryRule *>(rule.get())->boundary_states.clear();

	return isComplete;
}

//void GrainGrowthWithBoundaryCellularAutomata::start()
//{
//
//	if (rule)
//		delete rule;
//	rule = new GrainBoundaryRule();
//	int state = 0;
//	while (!step());
//	int stop = 0;
//}