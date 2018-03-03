#include "CellularAutomata.h"
#include "Cell.h"
#include "SPoint.h"

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
	this->cells = new unsigned short ** [this->m];
	//this->cells.resize(this->m);
	for (int i = 0 ; i < this->m; i ++)
	{
		this->cells[i] = new unsigned short *[this->n];
		//this->cells[i].resize(this->n);
		for (int j = 0; j < this->n; j++)
		{
			this->cells[i][j] = new unsigned short[this->o];
			//this->cells[i][j].resize(this->o);
			for (int k = 0; k < this->o; k++)
			{
				//this->cells[i][j][k].position = SPoint(i, j, k);
				this->cells[i][j][k] = 0;
			}
		}
	}
	this->nucleons_count = 0;
}

CellularAutomata::CellularAutomata(CellularAutomata & ca)
{
	this->m = ca.getSize()[0];
	this->n = ca.getSize()[1];
	this->o = ca.getSize()[2];

	this->cells = new unsigned short ** [this->m];
	//this->cells.resize(this->m);
	for (int i = 0; i < this->m; i++)
	{
		this->cells[i] = new unsigned short *[this->n];
		//this->cells[i].resize(this->n);
		for (int j = 0; j < this->n; j++)
		{
			this->cells[i][j] = new unsigned short[this->o];
			//this->cells[i][j].resize(this->o);
			for (int k = 0; k < this->o; k++)
			{
				//this->cells[i][j][k].position = SPoint(i, j, k);
				this->cells[i][j][k] = ca.cells[i][j][k];
			}
		}
	}
	this->nucleons_count = ca.nucleons_count;
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
			//this->cells[i][j].clear();
		}
		delete[] this->cells[i];
		//this->cells[i].clear();
	}
	delete[] this->cells;
	//this->cells.clear();
}

void CellularAutomata::copy(CellularAutomata & ca)
{
	this->m = ca.getSize()[0];
	this->n = ca.getSize()[1];
	this->o = ca.getSize()[2];

	for (int i = 0; i < this->m; i++)
	{
		for (int j = 0; j < this->n; j++)
		{
			for (int k = 0; k < this->o; k++)
			{
				
				//this->cells[i][j][k] = ca->getCells()[i][j][k];
				/*this->cells[i][j][k].position = SPoint(ca.getCells()[i][j][k].position.x,
					ca.getCells()[i][j][k].position.y,
					ca.getCells()[i][j][k].position.z);*/
			}
		}
	}
	this->nucleons_count = ca.nucleons_count;
}

/*	Pobieranie komórek	*/
unsigned short *** CellularAutomata::getCells()
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

