#pragma once

#include <memory>
#include<vector>

class Neighborhood
{
public:
	Neighborhood();
	Neighborhood(const Neighborhood &o);
	~Neighborhood();

	//Pobieranie s�siad�w
	virtual std::vector<unsigned int> get(const std::shared_ptr<class CellularAutomataSpace > & cellular_automata_space, unsigned int x, unsigned int y, unsigned int z);
	void setRadius(unsigned int r);

protected:
	//Promie� s�siedztwa
	int radius;
};
