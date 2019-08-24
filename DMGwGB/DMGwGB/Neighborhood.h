#pragma once

#include <memory>
#include<vector>

class Neighborhood
{
public:
	Neighborhood();
	Neighborhood(const Neighborhood &o);
	~Neighborhood();

	//Pobieranie s¹siadów
	virtual std::vector<unsigned int> get(const std::shared_ptr<class CellularAutomataSpace > & cellular_automata_space, unsigned int x, unsigned int y, unsigned int z);
	void setRadius(unsigned int r);

protected:
	//Promieñ s¹siedztwa
	int radius;
};
