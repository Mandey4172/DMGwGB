#pragma once

#include<vector>
#include<string>

enum class BoundaryContidionTypes
{
	Blocking,
	Periodic,
	Reflecting
};

class CellularAutomataSpace
{
public:
	CellularAutomataSpace(unsigned int m = 1, unsigned int n = 1, unsigned int o = 1);
	//Konstruktor kopiuj¹cy
	CellularAutomataSpace(const CellularAutomataSpace & ca);
	//Konstruktor przesuwaj¹cy
	CellularAutomataSpace(CellularAutomataSpace && ca);
	//Operator przepisania
	CellularAutomataSpace& operator=(const CellularAutomataSpace & ca);
	//Destruktor
	~CellularAutomataSpace();

	//Zapisu w obiekcie string
	std::string save() const;
	//Wczytaj z obiektu string
	//void load(const std::string &data);
	bool load(const std::string &path);

	//Pobieranie komórek
	inline unsigned int *** getCells() const;

	//Pobieranie rozmiaru : 0 - wszystkie wymiary, 1 - oœ X, 2 - oœ Y, 3 - oœ Z
	std::vector<unsigned int> getSize(const unsigned int n = 0) const;

	//Pobierz typ sasiedztwa
	BoundaryContidionTypes getBoundatyConditionType() const;
	//Ustaw typ sasiedztwa
	void setBoundaryContidion(BoundaryContidionTypes type);

	//Iloœæ zarodków
	unsigned int nucleons_count;
	//Iloœæ granic ziaren
	unsigned int boundarys_count;
	//Rozmiar na osi:
	unsigned int m;	//X
	unsigned int n;	//Y
	unsigned int o;	//Z

private:
	//Komórki
	unsigned int *** cells;
	//Warunki brzegowe
	BoundaryContidionTypes boundary_contidion;

	void constructSpace(unsigned int m, unsigned int n, unsigned int o);
	void destroySpace();
};
