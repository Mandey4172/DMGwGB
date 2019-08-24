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
	//Konstruktor kopiuj�cy
	CellularAutomataSpace(const CellularAutomataSpace & ca);
	//Konstruktor przesuwaj�cy
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

	//Pobieranie kom�rek
	inline unsigned int *** getCells() const;

	//Pobieranie rozmiaru : 0 - wszystkie wymiary, 1 - o� X, 2 - o� Y, 3 - o� Z
	std::vector<unsigned int> getSize(const unsigned int n = 0) const;

	//Pobierz typ sasiedztwa
	BoundaryContidionTypes getBoundatyConditionType() const;
	//Ustaw typ sasiedztwa
	void setBoundaryContidion(BoundaryContidionTypes type);

	//Ilo�� zarodk�w
	unsigned int nucleons_count;
	//Ilo�� granic ziaren
	unsigned int boundarys_count;
	//Rozmiar na osi:
	unsigned int m;	//X
	unsigned int n;	//Y
	unsigned int o;	//Z

private:
	//Kom�rki
	unsigned int *** cells;
	//Warunki brzegowe
	BoundaryContidionTypes boundary_contidion;

	void constructSpace(unsigned int m, unsigned int n, unsigned int o);
	void destroySpace();
};
