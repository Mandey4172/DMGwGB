#include "GrainBoundaryRule.h"

#include <algorithm>    
#include <vector>
#include <omp.h>


GrainBoundaryRule::GrainBoundaryRule()
{
}


GrainBoundaryRule::~GrainBoundaryRule()
{
}

/* Regó³a przejœcia dla wyszukiwania granic ziaren */
void GrainBoundaryRule::step(unsigned int * cell, std::vector<unsigned int> & neighborhood)
{
	if (!neighborhood.empty())
	{
		std::vector<unsigned int> cell_state;
		BoundaryNode new_node;
		//Tworzenie tablicy z unikalnymi stanami
		for (unsigned int n : neighborhood)
		{
			if (n <= this->grain_count)
			{
				if (std::find(cell_state.begin(), cell_state.end(), n) == cell_state.end())
				{
					cell_state.push_back(n);
				}
			}
		}
		//Sorkowanie tablicy z unikalnymi stanami otoczenia 
		std::sort(cell_state.begin(), cell_state.end());
		//Je¿eli istnieje wiecej ni¿ jeden stan w s¹siedztwie
		//komórka znajduje sie na granicy
		if (cell_state.size() > 1)
		{
			if (!this->boundary_states.empty())
			{
				//Sprawdzanie czy granica posiada opis w globalnej liœcie
				for (BoundaryNode b : this->boundary_states)
				{
					//Czy aktualne otoczenie jest takie samo jak otoczenie elementu z listy
					if (b.neighborhood_states == cell_state)
					{
						//Jezeli otoczenie jest zgodne przypisz stan i przerwij 
						*cell = b.state;
						return;
					}
				}
			}
			//Gdy nie istnieje opis w globalnej liœcie
			new_node.neighborhood_states = cell_state;
			new_node.state = this->grain_count + 1 + this->boundary_states.size();
			*cell = new_node.state;

			//Dodaj opis
			this->boundary_states.push_back(new_node);
		}
	}
}
	
