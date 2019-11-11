#pragma once

#include <memory>
#include<vector>

class Neighborhood
{
public:
	Neighborhood();
	Neighborhood(const Neighborhood& other);
	Neighborhood(Neighborhood&& other);

	Neighborhood& operator=(const Neighborhood& other);
	Neighborhood& operator=(Neighborhood&& other);

	virtual ~Neighborhood();


	virtual std::vector<unsigned int> get(const std::shared_ptr<class CellularAutomataSpace > & cellular_automata_space, unsigned int x, unsigned int y, unsigned int z) const = 0;
	void setRadius(unsigned int r);

protected:
	int radius = 1;
};
