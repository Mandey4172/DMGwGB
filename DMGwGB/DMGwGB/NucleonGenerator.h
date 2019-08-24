#pragma once
//TODO:: Usun
//#include"CellularAutomataSpace.h"
#include <memory>

class NucleonGenerator
{
public:
	NucleonGenerator();
	~NucleonGenerator();
	//Losowe zarodki
	void random(const std::shared_ptr< class CellularAutomataSpace > & ca, unsigned int quantity) const;
	//Losowe zarodki z minimalnym
	void random(const std::shared_ptr< class CellularAutomataSpace > & caa, unsigned int quantity, unsigned int r) const;

	//Regularna siatka
	void regular(const std::shared_ptr< class CellularAutomataSpace > & ca, unsigned int quantity_m, unsigned int quantity_n, unsigned int quantity_o) const;
	void regular(const std::shared_ptr< class CellularAutomataSpace > & ca, unsigned int quantity_m_n_o) const;

	////Podzia³ na mniejsze obszary
	//#void gradientA(CellularAutomata * ca, unsigned int grain_count, unsigned int cuts, unsigned int delta, unsigned int begin, short direction) const;
};
