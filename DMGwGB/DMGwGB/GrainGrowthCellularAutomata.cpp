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

//Pojedyñczy krok czasowy symulacji
bool GrainGrowthCellularAutomata::step()
{
	//Kopiowanie wynikowego automatu komórkowego
	std::shared_ptr< CellularAutomataSpace > cca = std::make_shared< CellularAutomataSpace >(*cellular_automata_space);
	//Pobieranie rozmiaru automatu
	int m = static_cast<int>(cellular_automata_space->m),
		n = static_cast<int>(cellular_automata_space->n),
		o = static_cast<int>(cellular_automata_space->o);
	//Zmienna informuj¹ca czy mikrostruktóra jest gotowa
	bool exit = true;
	//Wejœcie w obszar zrównoleglony
#pragma omp parallel
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			//Wspó³bierzne wykonanie pêtli
#pragma omp for schedule(static) nowait
			for (int k = 0; k < o; k++)
			{
				//Czy sprawdzana komórka jest pusta
				if (cellular_automata_space->getCells()[i][j][k] == 0)
				{
					//Pobieranie s¹siedztwa
					std::vector<unsigned int> neightborhood = neighborhood->get(cca, i, j, k);
					//Wykonanie regó³y dla komórki
					rule->check(&cellular_automata_space->getCells()[i][j][k], neightborhood);
					//Czy zmieni³ siê stan komórki
					if (cellular_automata_space->getCells()[i][j][k] > 0)
					{
						//Mikrostruktóra nie jest gotowa
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
//	//Generuj a¿ mikrostruktóra bêdzie gotowa
//	while (!step());
//}