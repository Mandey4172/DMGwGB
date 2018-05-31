#pragma once

#include"Cell.h"

#include<vector>

enum class BoundaryContidionTypes
{
	Blocking,
	Periodic
};

class CellularAutomata
{
public:
	CellularAutomata(unsigned int m = 1, unsigned int n = 1, unsigned int o = 1);
	CellularAutomata(CellularAutomata & ca);
	~CellularAutomata();

	void copy(CellularAutomata & ca);
	//Pobieranie kom�rek
	unsigned int *** getCells();
	//Pobieranie rozmiaru 0 - wszystkie wymiary, 1 - X, 2 - Y, 3 - Z
	std::vector<unsigned int> getSize(unsigned int n = 0);
	//Pobierz typ sasiedztwa 
	//BoundaryContidionTypes boundary_contidion;
	//Ustaw typ sasiedztwa 
	void setBoundaryContidion(BoundaryContidionTypes type);
private:
	//Rozmiar na osi:
	unsigned int m;	//X
	unsigned int n;	//Y
	unsigned int o;	//Z
	//Kom�rki
	unsigned int *** cells;
	
public:
	//Front automatu kom�rkowego
	bool *** front;
	//Ilo�� zarodk�w
	unsigned int nucleons_count;
	//Ilo�� granic ziaren
	unsigned int boundarys_count;
	//Warunki brzegowe
	BoundaryContidionTypes boundary_contidion;
};

