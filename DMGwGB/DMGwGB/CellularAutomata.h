#pragma once


#include<vector>

enum class BoundaryContidionTypes
{
	Blocking,
	Periodic,
	Reflecting
};

class CellularAutomata
{
public:
	CellularAutomata(unsigned int m = 1, unsigned int n = 1, unsigned int o = 1);
	CellularAutomata(const CellularAutomata & ca);
	CellularAutomata& operator=(const CellularAutomata & ca);
	~CellularAutomata();

	void copy(CellularAutomata & ca);
	//Pobieranie komórek
	unsigned int *** getCells() const;
	//Pobieranie rozmiaru 0 - wszystkie wymiary, 1 - X, 2 - Y, 3 - Z
	std::vector<unsigned int> getSize(unsigned int n = 0) const;
	//Pobierz typ sasiedztwa 
	//BoundaryContidionTypes boundary_contidion;
	//Ustaw typ sasiedztwa 
	void setBoundaryContidion(BoundaryContidionTypes type);
private:
	//Rozmiar na osi:
	unsigned int m;	//X
	unsigned int n;	//Y
	unsigned int o;	//Z
	//Komórki
	unsigned int *** cells;
	
public:
	//Front automatu komórkowego
	bool *** front;
	//Iloœæ zarodków
	unsigned int nucleons_count;
	//Iloœæ granic ziaren
	unsigned int boundarys_count;
	//Warunki brzegowe
	BoundaryContidionTypes boundary_contidion;
};

