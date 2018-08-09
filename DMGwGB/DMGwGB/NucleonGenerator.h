#pragma once

#include"CellularAutomata.h"

class NucleonGenerator
{
public:
	NucleonGenerator();
	~NucleonGenerator();
	//Losowe zarodki
	static void random(CellularAutomata * ca, unsigned int quantity, unsigned int grain_count );
	//Losowe zarodki z minimalnym odstêpem
	void random(CellularAutomata * ca, unsigned int quantity, unsigned int grain_count, unsigned int r);

	//Regularna siatka
	void regular(CellularAutomata * ca, unsigned int quantity_m, unsigned int quantity_n, unsigned int quantity_o, unsigned int grain_count);
	void regular(CellularAutomata * ca, unsigned int quantity_m_n_o, unsigned int grain_count);

	//Podzia³ na mniejsze obszary
	void gradientA(CellularAutomata * ca, unsigned int grain_count, unsigned int cuts, unsigned int delta, unsigned int begin, short direction);
};

