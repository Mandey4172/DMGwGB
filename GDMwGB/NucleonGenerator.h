#pragma once

#include"CellularAutomata.h"

class NucleonGenerator
{
public:
	NucleonGenerator();
	~NucleonGenerator();
	//Losowe zarodki
	static void random(CellularAutomata * ca, int quantity);
	//Losowe zarodki z minimalnym odst�pem
	void random(CellularAutomata * ca, int quantity, int r);

	//Regularna siatka
	void regular(CellularAutomata * ca, int quantity_m, int quantity_n, int quantity_o);
	void regular(CellularAutomata * ca, int quantity_m_n_o);

	//Podzia� na mniejsze obszary
	void gradientA(CellularAutomata * ca,int cuts, int delta, int begin, short direction);
};

