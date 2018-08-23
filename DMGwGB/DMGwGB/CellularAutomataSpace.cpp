#include "CellularAutomataSpace.h"

#include <sstream>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <regex>

// https://stackoverflow.com/questions/9435385/split-a-string-using-c11

std::vector<std::string> split(const std::string& input, const std::string& regex) {
	// passing -1 as the submatch index parameter performs splitting
	std::regex re(regex);
	std::sregex_token_iterator
		first{ input.begin(), input.end(), re, -1 },
		last;
	return { first, last };
}

/*  Konstruktor	*/
CellularAutomataSpace::CellularAutomataSpace(unsigned int nm, unsigned int nn, unsigned int no)
{
	//Wymiar w ka¿dj osi musi byæ wiêkszy od 0
	if (nm > 0)	this->m = nm;
	else				this->m = 1;
	if (nn > 0)	this->n = nn;
	else				this->n = 1;
	if (no > 0)	this->o = no;
	else				this->o = 1;
	//Twoznie komórek
	this->cells = new unsigned int ** [this->m];
	for (unsigned int i = 0 ; i < this->m; i ++)
	{
		this->cells[i] = new unsigned int *[this->n];
		for (unsigned int j = 0; j < this->n; j++)
		{
			this->cells[i][j] = new unsigned int[this->o];
			for (unsigned int k = 0; k < this->o; k++)
			{
				this->cells[i][j][k] = 0;
			}
		}
	}
	boundary_contidion = BoundaryContidionTypes::Blocking;
	this->nucleons_count = 0;
}

CellularAutomataSpace::CellularAutomataSpace(const CellularAutomataSpace & ca)
{
	this->m = ca.getSize()[0];
	this->n = ca.getSize()[1];
	this->o = ca.getSize()[2];

	this->cells = new unsigned int ** [this->m];
	//this->cells.resize(this->m);
	for (unsigned int i = 0; i < this->m; i++)
	{
		this->cells[i] = new unsigned int *[this->n];
		//this->cells[i].resize(this->n);
		for (unsigned int j = 0; j < this->n; j++)
		{
			this->cells[i][j] = new unsigned int[this->o];
			//this->cells[i][j].resize(this->o);
			for (unsigned int k = 0; k < this->o; k++)
			{
				this->cells[i][j][k] = ca.getCells()[i][j][k];
			}
		}
	}
	nucleons_count = ca.nucleons_count;
	boundary_contidion = ca.boundary_contidion;
}
CellularAutomataSpace& CellularAutomataSpace::operator=(const CellularAutomataSpace & ca)
{
	CellularAutomataSpace instance(ca);
	return instance;
}
/*	 Dstruktor	*/
CellularAutomataSpace::~CellularAutomataSpace()
{
	//Usuwanie komórek
	if (this->cells)
	{
		for (unsigned int i = 0; i < this->m; i++)
		{
			for (unsigned int j = 0; j < this->n; j++)
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

std::string CellularAutomataSpace::save() const
{
	std::string save;
	save = std::to_string(this->nucleons_count) + "\n\n";
	for (unsigned int i = 0; i < m; i++)
	{
		for (unsigned int j = 0; j < n; j++)
		{
			for (unsigned int k = 0; k < o; k++)
			{
				save += std::to_string(cells[i][j][k]) + " ";
			}
			save += "\n";
		}
		save += "\n";
	}
	return save;
}

void CellularAutomataSpace::load(std::string data)
{
	std::vector<std::vector<std::vector<std::string>>> vcells;

	unsigned int a = 0, b = 0, c = 0;
	std::vector<std::string> firstCut = split(data,"\n\n");

	int new_nucleons_count = std::stoi(firstCut[0]);
	firstCut.erase(firstCut.begin());

	a = firstCut.size();
	for (std::string first : firstCut)
	{
		std::vector<std::vector<std::string>> filler;
		std::vector<std::string> secondCut = split(first, "\n");
		b = secondCut.size() > b ? secondCut.size() : b;
		for (std::string second : secondCut)
		{
			std::vector<std::string> sfiller;
			std::vector<std::string> thirdCut = split(second, " ");
			c = thirdCut.size() > c ? thirdCut.size() : c;
			for (std::string third : thirdCut)
			{
				sfiller.push_back(third);
			}
			filler.push_back(sfiller);
		}
		vcells.push_back(filler);
	}
	
	//Destructor call
	this->CellularAutomataSpace::~CellularAutomataSpace();
	//Constructor call
	this->CellularAutomataSpace::CellularAutomataSpace(a, b, c);
	this->nucleons_count = new_nucleons_count;
	for (unsigned int i = 0 ; i < a; i++)
	{
		for (unsigned int j = 0; j < b; j++)
		{
			for (unsigned int k = 0; k < c; k++)
			{
				cells[i][j][k] = static_cast<unsigned int>(std::stoi(vcells[i][j][k]));
			}
		}
	}
}


/*	Pobieranie komórek	*/
unsigned int *** CellularAutomataSpace::getCells() const
{
	return cells;
}

BoundaryContidionTypes CellularAutomataSpace::getBoundatyConditionType()
{
	return boundary_contidion;
}

std::vector<unsigned int> CellularAutomataSpace::getSize(const unsigned int n) const
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

//BoundaryContidionTypes CellularAutomataSpace::getBoundaryContidion()
//{
//	return boundary_contidion;
//}

void CellularAutomataSpace::setBoundaryContidion(BoundaryContidionTypes type)
{
	boundary_contidion = type;
}

