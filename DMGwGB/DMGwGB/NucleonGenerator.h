#pragma once
#include <memory>

class NucleonGenerator
{
public:
	NucleonGenerator();
	~NucleonGenerator();

	void random(const std::shared_ptr< class CellularAutomataSpace > & ca, unsigned int quantity) const;
	void random(const std::shared_ptr< class CellularAutomataSpace > & caa, unsigned int quantity, unsigned int r) const;

	void regular(const std::shared_ptr< class CellularAutomataSpace > & ca, unsigned int quantity_m, unsigned int quantity_n, unsigned int quantity_o) const;
	void regular(const std::shared_ptr< class CellularAutomataSpace > & ca, unsigned int quantity_m_n_o) const;

	//#void gradientA(CellularAutomata * ca, unsigned int grain_count, unsigned int cuts, unsigned int delta, unsigned int begin, short direction) const;
};
