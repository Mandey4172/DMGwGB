#pragma once
#include "CellularAutomata.h"

//In simulation, the grains grow until there is no empty cell inside,
//next step creates grain boundary representation in microstructure.

class GrainGrowthWithBoundaryCellularAutomata :
	public CellularAutomata
{
public:
	GrainGrowthWithBoundaryCellularAutomata();

	void setBoundaryNeighborhood(const std::shared_ptr< class Neighborhood > & neighborhood);
	std::shared_ptr< class Neighborhood > getBoundaryNeighborhood();

	virtual bool step() override;

	unsigned int getGrainSize();
	bool souldFuseAfterSimulation();
	void setFuseAfterSimulation(bool fuseAfterSimulation);
	void setGrainSize(unsigned int size);

protected:

	unsigned int grainSize;
	bool bFuseAfterSimulation;

	std::shared_ptr< class Neighborhood > boundary_neighborhood;
};
