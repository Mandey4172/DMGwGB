#include "CellularAutomata.h"

/*  Konstruktor	*/
CellularAutomata::CellularAutomata(unsigned int nm, unsigned int nn, unsigned int no)
{
	//Wymiar w ka¿dj osi musi byæ wiêkszy od 0
	if (this->m > 0)	this->m = nm;
	else				this->m = 1;
	if (this->n > 0)	this->n = nn;
	else				this->n = 1;
	if (this->o > 0)	this->o = no;
	else				this->o = 1;
	//Twoznie komórek
	this->cells = new Cell ** [this->m];
	for (int i = 0 ; i < this->m; i ++)
	{
		this->cells[i] = new Cell *[this->n];
		for (int j = 0; j < this->n; j++)
		{
			this->cells[i][j] = new Cell[this->o];
		}
	}
	this->nucleon_count = 0;
}
/*	 Dstruktor	*/
CellularAutomata::~CellularAutomata()
{
	//Usuwanie komórek
	for (int i = 0; i < this->m; i++)
	{
		for (int j = 0; j < this->n; j++)
		{
			delete[] this->cells[i][j];
		}
		delete[] this->cells[i];
	}
	delete[] this->cells;
}
/*	Pobieranie komórek	*/
Cell *** CellularAutomata::getCells()
{
	return cells;
}

std::vector<unsigned int> CellularAutomata::getSize(unsigned int n)
{
	std::vector<unsigned int> size;
	if (n == 0)
	{
		size.push_back(this->m);
		size.push_back(this->n);
		size.push_back(this->o);
	}
	if (n == 1)
	{
		size.push_back(this->m);
	}
	if (n == 2)
	{
		size.push_back(this->n);
	}
	if (n == 3)
	{
		size.push_back(this->o);
	}
	return size;
}

