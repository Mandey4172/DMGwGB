#pragma once

#include"CellularAutomataSpace.h"

class NucleonGenerator
{
public:
	NucleonGenerator();
	~NucleonGenerator();
	//Losowe zarodki
	void random(CellularAutomataSpace * ca, unsigned int quantity, unsigned int grain_count ) const;
	//Losowe zarodki z minimalnym odstêpem
	void random(CellularAutomataSpace * ca, unsigned int quantity, unsigned int grain_count, unsigned int r) const;

	//Regularna siatka
	void regular(CellularAutomataSpace * ca, unsigned int quantity_m, unsigned int quantity_n, unsigned int quantity_o, unsigned int grain_count) const;
	void regular(CellularAutomataSpace * ca, unsigned int quantity_m_n_o, unsigned int grain_count) const;

	////Podzia³ na mniejsze obszary
	//void gradientA(CellularAutomata * ca, unsigned int grain_count, unsigned int cuts, unsigned int delta, unsigned int begin, short direction) const;
};

