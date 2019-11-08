#pragma once
#include "Neighborhood.h"
class HexagonalNeighborhood :
	public Neighborhood
{
public:
	HexagonalNeighborhood();
	~HexagonalNeighborhood();

	virtual std::vector<unsigned int> get(const std::shared_ptr<class CellularAutomataSpace > & cellular_automata_space, unsigned int x, unsigned int y, unsigned int z) const override;
private:
	std::vector<unsigned int> getXA(const std::shared_ptr<class CellularAutomataSpace > & cellular_automata_space, unsigned int x, unsigned int y, unsigned int z) const;
	std::vector<unsigned int> getXB(const std::shared_ptr<class CellularAutomataSpace > & cellular_automata_space, unsigned int x, unsigned int y, unsigned int z) const;
	std::vector<unsigned int> getYA(const std::shared_ptr<class CellularAutomataSpace > & cellular_automata_space, unsigned int x, unsigned int y, unsigned int z) const;
	std::vector<unsigned int> getYB(const std::shared_ptr<class CellularAutomataSpace > & cellular_automata_space, unsigned int x, unsigned int y, unsigned int z) const;
	std::vector<unsigned int> getZA(const std::shared_ptr<class CellularAutomataSpace > & cellular_automata_space, unsigned int x, unsigned int y, unsigned int z) const;
	std::vector<unsigned int> getZB(const std::shared_ptr<class CellularAutomataSpace > & cellular_automata_space, unsigned int x, unsigned int y, unsigned int z) const;
};
