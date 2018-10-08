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
	this->m = ca.m;
	this->n = ca.n;
	this->o = ca.o;

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
	//save = std::to_string(this->nucleons_count) + "\n\n";
	for (unsigned int i = 0; i < m; i++)
	{
		for (unsigned int j = 0; j < n; j++)
		{
			for (unsigned int k = 0; k < o; k++)
			{
				save += std::to_string(i) + " " +
					std::to_string(j) + " " +
					std::to_string(k) + " " +
					std::to_string(cells[i][j][k]) + "\n";
			}
		}
	}
	return save;
}

void CellularAutomataSpace::load(const std::string &data)
{
	struct Chunk
	{
		Chunk() : x(0), y(0), z(0), state(0) {};
		unsigned int x;
		unsigned int y;
		unsigned int z;
		unsigned int state;
	};
	std::vector<Chunk> cell_chunks;
	unsigned int	a = 0,
					b = 0, 
					c = 0,
					smax = 0;
	{
		std::vector<std::string> data_chunks = split(data, "\n");
		#pragma omp parallel for schedule(static)
		for (int i = 0; i < data_chunks.size(); i++)
		{
			std::string data_chunk = data_chunks[i];
			Chunk cell_chunk;
			std::vector<std::string> string_chunk = split(data_chunk, " ");
			if (string_chunk.size() == 4)
			{
				cell_chunk.x = static_cast<int>(std::stoi(string_chunk[0]));
				if (cell_chunk.x > a) a = cell_chunk.x;
				cell_chunk.y = static_cast<int>(std::stoi(string_chunk[1]));
				if (cell_chunk.y > b) b = cell_chunk.y;
				cell_chunk.z = static_cast<int>(std::stoi(string_chunk[2]));
				if (cell_chunk.z > c) c = cell_chunk.z;
				cell_chunk.state = static_cast<int>(std::stoi(string_chunk[3]));
				if (cell_chunk.state > smax) smax = cell_chunk.state;

				#pragma omp critical
				cell_chunks.push_back(cell_chunk);
			}
		}
	}
	//Destructor call
	this->CellularAutomataSpace::~CellularAutomataSpace();
	//Constructor call
	this->CellularAutomataSpace::CellularAutomataSpace(a + 1, b + 1, c + 1);
	this->nucleons_count = smax;

	#pragma omp parallel for schedule(static)
	for (int i = 0; i < cell_chunks.size(); i++)
	{
		Chunk chunk = cell_chunks[i];
		cells[chunk.x][chunk.y][chunk.z] = chunk.state;
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

void CellularAutomataSpace::setBoundaryContidion(BoundaryContidionTypes type)
{
	boundary_contidion = type;
}

