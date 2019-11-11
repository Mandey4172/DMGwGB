#pragma once
#include"Neighborhood.h"

class PentagonalNeighborhood : public Neighborhood
{
public:
	std::vector<unsigned int> get(const std::shared_ptr<class CellularAutomataSpace > & cellular_automata_space, unsigned int x, unsigned int y, unsigned int z) const override;
private:
	std::vector<unsigned int> getFront(const std::shared_ptr<class CellularAutomataSpace >& cellular_automata_space, unsigned int x, unsigned int y, unsigned int z) const;
	std::vector<unsigned int> getBack(const std::shared_ptr<class CellularAutomataSpace >& cellular_automata_space, unsigned int x, unsigned int y, unsigned int z) const;
	std::vector<unsigned int> getLeft(const std::shared_ptr<class CellularAutomataSpace >& cellular_automata_space, unsigned int x, unsigned int y, unsigned int z) const;
	std::vector<unsigned int> getRight(const std::shared_ptr<class CellularAutomataSpace >& cellular_automata_space, unsigned int x, unsigned int y, unsigned int z)const;
	std::vector<unsigned int> getTop(const std::shared_ptr<class CellularAutomataSpace >& cellular_automata_space, unsigned int x, unsigned int y, unsigned int z) const;
	std::vector<unsigned int> getBottom(const std::shared_ptr<class CellularAutomataSpace >& cellular_automata_space, unsigned int x, unsigned int y, unsigned int z)const;
};
