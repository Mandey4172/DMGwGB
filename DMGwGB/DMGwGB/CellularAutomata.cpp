#include "CellularAutomata.h"


/*  Konstruktor	*/
CellularAutomata::CellularAutomata(unsigned int nm, unsigned int nn, unsigned int no)
{
	//Wymiar w ka�dj osi musi by� wi�kszy od 0
	if (nm > 0)	this->m = nm;
	else				this->m = 1;
	if (nn > 0)	this->n = nn;
	else				this->n = 1;
	if (no > 0)	this->o = no;
	else				this->o = 1;
	//Twoznie kom�rek
	this->cells = new unsigned int ** [this->m];
	for (int i = 0 ; i < this->m; i ++)
	{
		this->cells[i] = new unsigned int *[this->n];
		for (int j = 0; j < this->n; j++)
		{
			this->cells[i][j] = new unsigned int[this->o];
			for (int k = 0; k < this->o; k++)
			{
				this->cells[i][j][k] = 0;
			}
		}
	}
	boundary_contidion = BoundaryContidionTypes::Blocking;
	this->nucleons_count = 0;
}

CellularAutomata::CellularAutomata(const CellularAutomata & ca)
{
	this->m = ca.getSize()[0];
	this->n = ca.getSize()[1];
	this->o = ca.getSize()[2];

	this->cells = new unsigned int ** [this->m];
	//this->cells.resize(this->m);
	for (int i = 0; i < this->m; i++)
	{
		this->cells[i] = new unsigned int *[this->n];
		//this->cells[i].resize(this->n);
		for (int j = 0; j < this->n; j++)
		{
			this->cells[i][j] = new unsigned int[this->o];
			//this->cells[i][j].resize(this->o);
			for (int k = 0; k < this->o; k++)
			{
				this->cells[i][j][k] = ca.getCells()[i][j][k];
			}
		}
	}
	nucleons_count = ca.nucleons_count;
	boundary_contidion = ca.boundary_contidion;
}
CellularAutomata& CellularAutomata::operator=(const CellularAutomata & ca)
{
	CellularAutomata instance(ca);
	return instance;
}
/*	 Dstruktor	*/
CellularAutomata::~CellularAutomata()
{
	//Usuwanie kom�rek
	if (this->cells)
	{
		for (int i = 0; i < this->m; i++)
		{
			for (int j = 0; j < this->n; j++)
			{
				if (this->cells[i][j])
				{
					delete[] this->cells[i][j];
				}
			}
			if (this->cells[i])
			{
				delete[] this->cells[i];
			}
		}
		delete[] this->cells;
	}
}

/*	Pobieranie kom�rek	*/
unsigned int *** CellularAutomata::getCells() const
{
	return cells;
}

BoundaryContidionTypes CellularAutomata::getBoundatyConditionType()
{
	return boundary_contidion;
}

std::vector<unsigned int> CellularAutomata::getSize(const unsigned int n) const
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

//BoundaryContidionTypes CellularAutomata::getBoundaryContidion()
//{
//	return boundary_contidion;
//}

void CellularAutomata::setBoundaryContidion(BoundaryContidionTypes type)
{
	boundary_contidion = type;
}

