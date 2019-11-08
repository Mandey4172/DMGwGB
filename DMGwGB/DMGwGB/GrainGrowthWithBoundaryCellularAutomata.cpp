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

	GrainGrowthCellularAutomata grainGrowth;
	grainGrowth.setNeighborhood(neighborhood);
	grainGrowth.setCellularAutomataSpace(cellular_automata_space);
	grainGrowth.start();
	grainGrowth.setNeighborhood(nullptr);
	grainGrowth.setCellularAutomataSpace(nullptr);

	unsigned int m = cellular_automata_space->getSizeOnXAxis(),
				 n = cellular_automata_space->getSizeOnYAxis(),
				 o = cellular_automata_space->getSizeOnZAxis();

	GrainGrowthCellularAutomata grainGrowthCopy;
	grainGrowthCopy.setCellularAutomataSpace(std::make_shared< CellularAutomataSpace >(m, n, o));

	rule->setGrainCount(cellular_automata_space->getNucleonsCount());

//#pragma omp parallel
	for (unsigned int i = 0; i < m; i++)
	{
		for (unsigned int j = 0; j < n; j++)
		{
//#pragma omp for schedule(static) nowait
			for (unsigned int k = 0; k < o; k++)
			{
				MooreNeighborhood mooreNeighborhood;
				std::vector<unsigned int> neightborhood = mooreNeighborhood.get(cellular_automata_space, i, j, k);

				rule->transition(&grainGrowthCopy.getCellularAutomataSpace()->getCells()[i][j][k], neightborhood);
			}
		}
	}
	bool work = true;

	for (unsigned int x = 0; (x < m*n*o) && work; x++)
	{
		work = false;
		GrainGrowthCellularAutomata grainGrowthWithGrains;
		grainGrowthWithGrains.setCellularAutomataSpace(std::make_shared< CellularAutomataSpace >(*grainGrowthCopy.getCellularAutomataSpace()));
//#pragma omp parallel
		for (unsigned int i = 0; i < m; i++)
		{
			for (unsigned int j = 0; j < n; j++)
			{
//#pragma omp for schedule(static) nowait
				for (unsigned int k = 0; k < o; k++)
				{
					if (grainGrowthWithGrains.getCellularAutomataSpace()->getCells()[i][j][k] > 0)
					{
						MooreNeighborhood mooreNeighborhood;
						mooreNeighborhood.setRadius(2);
						std::vector<unsigned int> neightborhood = mooreNeighborhood.get(grainGrowthWithGrains.getCellularAutomataSpace(), i, j, k);

						static_cast<GrainBoundaryRule *>(rule.get())->clear(&grainGrowthCopy.getCellularAutomataSpace()->getCells()[i][j][k], neightborhood);
						if (grainGrowthCopy.getCellularAutomataSpace()->getCells()[i][j][k] != grainGrowthWithGrains.getCellularAutomataSpace()->getCells()[i][j][k])
						{
							work = true;
						}
					}
				}
			}
		}
	}

	grainGrowthCopy.setNeighborhood(boundary_neighborhood);
	if (grainSize > 1)
	{
		for (unsigned int i = 1; i < grainSize; i++)
		{
			grainGrowthCopy.step();
		}
	}
	grainGrowthCopy.setNeighborhood(nullptr);

	if (bFuseAfterSimulation)
	{
//#pragma omp parallel
		for (unsigned int i = 0; i < m; i++)
		{
			for (unsigned int j = 0; j < n; j++)
			{
//#pragma omp for schedule(static) nowait
				for (unsigned int k = 0; k < o; k++)
				{
					if (grainGrowthCopy.getCellularAutomataSpace()->getCells()[i][j][k] > 0)
					{
						getCellularAutomataSpace()->getCells()[i][j][k] = grainGrowthCopy.getCellularAutomataSpace()->getCells()[i][j][k];
					}
				}
			}
		}
	}
	else
	{
		setCellularAutomataSpace(grainGrowthCopy.getCellularAutomataSpace());
		grainGrowthCopy.setCellularAutomataSpace(nullptr);
	}

	static_cast<GrainBoundaryRule *>(rule.get())->boundary_states.clear();

	return isComplete;
}

unsigned int GrainGrowthWithBoundaryCellularAutomata::getGrainSize()
{
	return grainSize;
}

bool GrainGrowthWithBoundaryCellularAutomata::souldFuseAfterSimulation()
{
	return bFuseAfterSimulation;
}

void GrainGrowthWithBoundaryCellularAutomata::setFuseAfterSimulation(bool fuseAfterSimulation)
{
	bFuseAfterSimulation = fuseAfterSimulation;
}

void GrainGrowthWithBoundaryCellularAutomata::setGrainSize(unsigned int size)
{
	grainSize = size;
}
