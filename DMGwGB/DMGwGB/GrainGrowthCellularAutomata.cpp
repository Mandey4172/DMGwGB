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

GrainGrowthCellularAutomata::~GrainGrowthCellularAutomata()
{
}

//Pojedy�czy krok czasowy symulacji
bool GrainGrowthCellularAutomata::step()
{
	//Kopiowanie wynikowego automatu kom�rkowego
	std::shared_ptr< CellularAutomataSpace > cca = std::make_shared< CellularAutomataSpace >(*cellular_automata_space);
	//Pobieranie rozmiaru automatu
	int m = static_cast<int>(cellular_automata_space->m),
		n = static_cast<int>(cellular_automata_space->n),
		o = static_cast<int>(cellular_automata_space->o);
	//Zmienna informuj�ca czy mikrostrukt�ra jest gotowa
	bool exit = true;
	//Wej�cie w obszar zr�wnoleglony
#pragma omp parallel
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			//Wsp�bierzne wykonanie p�tli
#pragma omp for schedule(static) nowait
			for (int k = 0; k < o; k++)
			{
				//Czy sprawdzana kom�rka jest pusta
				if (cellular_automata_space->getCells()[i][j][k] == 0)
				{
					//Pobieranie s�siedztwa
					std::vector<unsigned int> neightborhood = neighborhood->get(cca, i, j, k);
					//Wykonanie reg�y dla kom�rki
					rule->check(&cellular_automata_space->getCells()[i][j][k], neightborhood);
					//Czy zmieni� si� stan kom�rki
					if (cellular_automata_space->getCells()[i][j][k] > 0)
					{
						//Mikrostrukt�ra nie jest gotowa
						exit = false;
					}
				}
			}
		}
	}

	return exit;
}

//
//void GrainGrowthCellularAutomata::start()
//{
//	//Generuj a� mikrostrukt�ra b�dzie gotowa
//	while (!step());
//}