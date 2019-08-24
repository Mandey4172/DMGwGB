#pragma once
#include "CellularAutomata.h"

class GrainGrowthWithBoundaryCellularAutomata :
	public CellularAutomata
{
public:
	GrainGrowthWithBoundaryCellularAutomata();

	void setBoundaryNeighborhood(const std::shared_ptr< class Neighborhood > & neighborhood);
	std::shared_ptr< class Neighborhood > getBoundaryNeighborhood();

	virtual bool step() override;

	unsigned int grainSize;
	bool bFuseAfterSimulation;

protected:
	std::shared_ptr< class Neighborhood > boundary_neighborhood;
};
