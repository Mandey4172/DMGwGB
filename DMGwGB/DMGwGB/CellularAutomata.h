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
	//Konstruktor kopiuj¹cy
	CellularAutomata(const CellularAutomata & ca);
	//Operator przepisania
	CellularAutomata& operator=(const CellularAutomata & ca);
	//Destruktor
	~CellularAutomata();

	//Pobieranie komórek
	unsigned int *** getCells() const;
	
	//Pobieranie rozmiaru : 0 - wszystkie wymiary, 1 - oœ X, 2 - oœ Y, 3 - oœ Z
	std::vector<unsigned int> getSize(const unsigned int n = 0) const;
	
	//Pobierz typ sasiedztwa
	BoundaryContidionTypes getBoundatyConditionType();
	//Ustaw typ sasiedztwa 
	void setBoundaryContidion(BoundaryContidionTypes type);

	//Iloœæ zarodków
	unsigned int nucleons_count;
	//Iloœæ granic ziaren
	unsigned int boundarys_count;

private:
	//Rozmiar na osi:
	unsigned int m;	//X
	unsigned int n;	//Y
	unsigned int o;	//Z
	//Komórki
	unsigned int *** cells;
	//Warunki brzegowe
	BoundaryContidionTypes boundary_contidion;
};

