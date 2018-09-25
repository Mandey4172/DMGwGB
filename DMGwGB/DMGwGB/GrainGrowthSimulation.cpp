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

//Pojedy�czy krok czasowy symulacji
bool GrainGrowthCellularAutomata::step()
{
	//Kopiowanie wynikowego automatu kom�rkowego
	CellularAutomataSpace * cca = new CellularAutomataSpace(*this->cellularautomata);
	//Pobieranie rozmiaru automatu
	int m = static_cast<int>(cellularautomata->getSize()[0]),
		n = static_cast<int>(cellularautomata->getSize()[1]),
		o = static_cast<int>(cellularautomata->getSize()[2]);
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
				if(this->cellularautomata->getCells()[i][j][k] == 0)
				{
					//Pobieranie s�siedztwa
					std::vector<unsigned int> neightborhood = this->neighborhood->get(cca, i, j, k);
					//Wykonanie reg�y dla kom�rki
					this->rule->check(&this->cellularautomata->getCells()[i][j][k], neightborhood);
					//Czy zmieni� si� stan kom�rki
					if (this->cellularautomata->getCells()[i][j][k] > 0)
					{
						//Mikrostrukt�ra nie jest gotowa
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
	//Generuj a� mikrostrukt�ra b�dzie gotowa
	while (!step());
}
