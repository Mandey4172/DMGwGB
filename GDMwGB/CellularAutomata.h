#pragma once

#include"Cell.h"

#include<vector>

class CellularAutomata
{
public:
	CellularAutomata(unsigned int m = 1, unsigned int n = 1, unsigned int o = 1);
	~CellularAutomata();
	//Pobieranie komórek
	Cell *** getCells();
	std::vector<unsigned int> getSize(unsigned int n = 0);

private:
	//Rozmiar na osi:
	unsigned int m;	//X
	unsigned int n;	//Y
	unsigned int o;	//Z
	//Komórki
	Cell *** cells;
};

