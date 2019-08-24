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

/* Regu³a przejœcia dla wyszukiwania granic ziaren */
void GrainBoundaryRule::check(unsigned int * cell, std::vector<unsigned int> & neighborhood)
{
	if (!neighborhood.empty())
	{
		std::vector<unsigned int> unique_grains;
		BoundaryNode new_node;
		//Tworzenie tablicy z unikalnymi stanami
		for (unsigned int n : neighborhood)
		{
			if (n <= grain_count)
			{
				if (std::find(unique_grains.begin(), unique_grains.end(), n) == unique_grains.end())
				{
					unique_grains.push_back(n);
				}
			}
		}
		//Sorkowanie tablicy z unikalnymi stanami otoczenia
		std::sort(unique_grains.begin(), unique_grains.end());
		//
		bool exist = false;
		//Je¿eli istnieje wiecej ni¿ jeden stan w s¹siedztwie
		//komórka znajduje sie na granicy
#pragma omp critical
		{
			if (unique_grains.size() > 1)
			{
				if (!boundary_states.empty())
				{
					//Sprawdzanie czy granica posiada opis w globalnej liœcie
					for (std::vector<BoundaryNode>::reverse_iterator b = boundary_states.rbegin(); b != boundary_states.rend(); b++)
					{
						//Czy aktualne otoczenie jest takie samo jak otoczenie elementu z listy
						if (b->neighborhood_states == unique_grains)
						{
							//Jezeli otoczenie jest zgodne przypisz stan i przerwij
							*cell = b->state;
							exist = true;
						}
					}
				}
				if (!exist)
				{
					//Gdy nie istnieje opis w globalnej liœcie
					new_node.neighborhood_states = unique_grains;
					new_node.state = static_cast<unsigned int>(grain_count + 1 + boundary_states.size());
					*cell = new_node.state;

					//Dodaj opis
					boundary_states.push_back(new_node);
				}
			}
		}
	}
}

void GrainBoundaryRule::clear(unsigned int * cell, std::vector<unsigned int>& neighborhood) const
{
	if (!neighborhood.empty())
	{
		std::vector<unsigned int> unique_grains;
		std::vector<unsigned int> count_grain;

		unique_grains.push_back(*cell);
		count_grain.push_back(1);

		for (unsigned int n : neighborhood)
		{
			if (n >= grain_count)
			{
				//Sprawdzanie czy stan w tablicy s¹siadów s¹siedztwa istnieje
				bool exist = false;
				if (!unique_grains.empty())
				{
					for (int i = 0; i < unique_grains.size(); i++)
					{
						if (unique_grains[i] == n)
						{
							//Gdy stan istnieje w tablicy z unikalnymi stanami
							exist = true;
							count_grain[i]++;
							break;
						}
					}
				}
				if (!exist)
				{
					//Gdy stan istnieje w tablicy z unikalnymi stanami.
					//Dodaj go do tablicy.
					unique_grains.push_back(n);
					count_grain.push_back(1);
				}
			}
		}
		//Wybór ziarna które najczêœciej wystêpuje
		if (!unique_grains.empty())
		{
			int max = 0;
			for (int i = 1; i < unique_grains.size(); i++)
			{
				if (count_grain[max] < count_grain[i])
				{
					max = i;
				}
			}
			*cell = unique_grains[max];
		}
	}
}