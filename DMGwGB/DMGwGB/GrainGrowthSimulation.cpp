#include "GrainGrowthCellularAutomata.h"

#include "CellularAutomataSpace.h"
#include "Neighborhood.h"
#include "CellularAutomataRule.h"
#include "SPoint.h"

#include "MooreNeighborhood.h"
#include "GrainGrowthRule.h"

#include<omp.h>


GrainGrowthCellularAutomata::GrainGrowthCellularAutomata()
{
	this->cellularautomata = new CellularAutomataSpace(10, 10, 10);
	this->neighborhood = new MooreNeighborhood();
	//new VonNeummanNeighborhood();
	//new HexagonalNeighborhood();
	//new PentagonalNeighborhood();
	this->rule = new GrainGrowthRule();
}

GrainGrowthCellularAutomata::~GrainGrowthCellularAutomata()
{

}

//Pojedyñczy krok czasowy symulacji
bool GrainGrowthCellularAutomata::step()
{
	//Kopiowanie wynikowego automatu komórkowego
	CellularAutomataSpace * cca = new CellularAutomataSpace(*this->cellularautomata);
	//Pobieranie rozmiaru automatu
	int m = static_cast<int>(cellularautomata->getSize()[0]),
		n = static_cast<int>(cellularautomata->getSize()[1]),
		o = static_cast<int>(cellularautomata->getSize()[2]);
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
				if(this->cellularautomata->getCells()[i][j][k] == 0)
				{
					//Pobieranie s¹siedztwa
					std::vector<unsigned int> neightborhood = this->neighborhood->get(cca, i, j, k);
					//Wykonanie regó³y dla komórki
					this->rule->check(&this->cellularautomata->getCells()[i][j][k], neightborhood);
					//Czy zmieni³ siê stan komórki
					if (this->cellularautomata->getCells()[i][j][k] > 0)
					{
						//Mikrostruktóra nie jest gotowa
						exit = false;
					}
				}
			}
		}
	}

	delete cca;

	return exit;
}

//
void GrainGrowthCellularAutomata::start()
{
	//Generuj a¿ mikrostruktóra bêdzie gotowa
	while (!step());
}
