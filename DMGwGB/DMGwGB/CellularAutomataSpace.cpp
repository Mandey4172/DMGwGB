#include "CellularAutomataSpace.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <regex>
#include <sstream>
#include <streambuf>

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
CellularAutomataSpace::CellularAutomataSpace(unsigned int m, unsigned int n, unsigned int o)
{
	constructSpace(m, n, o);
	boundary_contidion = BoundaryContidionTypes::Blocking;
	nucleons_count = 0;
	boundarys_count = 0;
}

CellularAutomataSpace::CellularAutomataSpace(const CellularAutomataSpace & ca)
{
	m = ca.m;
	n = ca.n;
	o = ca.o;

	cells = new unsigned int **[m];
	//cells.resize(m);
	for (unsigned int i = 0; i < m; i++)
	{
		cells[i] = new unsigned int *[n];
		//cells[i].resize(n);
		for (unsigned int j = 0; j < n; j++)
		{
			cells[i][j] = new unsigned int[o];
			std::copy(ca.cells[i][j], ca.cells[i][j] + o, getCells()[i][j]);
			//for (unsigned int k = 0; k < o; k++)
			//{
			//	cells[i][j][k] = ca.getCells()[i][j][k];
			//}
		}
	}
	nucleons_count = ca.nucleons_count;
	boundary_contidion = ca.boundary_contidion;
	boundarys_count = ca.boundarys_count;

}
CellularAutomataSpace::CellularAutomataSpace(CellularAutomataSpace && ca)
{
	cells = ca.cells;
	ca.cells = nullptr;
}
CellularAutomataSpace& CellularAutomataSpace::operator=(const CellularAutomataSpace & ca)
{
	CellularAutomataSpace instance(ca);
	return instance;
}
/*	 Dstruktor	*/
CellularAutomataSpace::~CellularAutomataSpace()
{
	destroySpace();
}

std::string CellularAutomataSpace::save() const
{
	std::string save;
	//save = std::to_string(nucleons_count) + "\n\n";
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

bool CellularAutomataSpace::load(const std::string &path)
{
	struct Chunk
	{
		Chunk() : x(0), y(0), z(0), state(0) {};
		unsigned int x;
		unsigned int y;
		unsigned int z;
		unsigned int state;
	};

	std::ifstream file{ path, std::ios::in | std::ios::binary };
	if (file)
	{
		std::string data;

		file.seekg(0, std::ios::end);
		data.resize(file.tellg());
		file.seekg(0, std::ios::beg);
		file.read(&data[0], data.size());
		file.close();

		std::vector<Chunk> cell_chunks;
		unsigned int a = 0, b = 0, c = 0,
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
					cell_chunk.z = std::stoi(string_chunk[2]);
					if (cell_chunk.z > c) c = cell_chunk.z;
					cell_chunk.state = std::stoi(string_chunk[3]);
					if (cell_chunk.state > smax) smax = cell_chunk.state;

#pragma omp critical
					cell_chunks.push_back(cell_chunk);
				}
			}
		}
		destroySpace();
		constructSpace(a + 1, b + 1, c + 1);
		nucleons_count = smax;

#pragma omp parallel for schedule(static)
		for (int i = 0; i < cell_chunks.size(); i++)
		{
			Chunk chunk = cell_chunks[i];
			cells[chunk.x][chunk.y][chunk.z] = chunk.state;
		}
	}
}

/*	Pobieranie kom�rek	*/
unsigned int *** CellularAutomataSpace::getCells() const
{
	return cells;
}

BoundaryContidionTypes CellularAutomataSpace::getBoundatyConditionType() const
{
	return boundary_contidion;
}

std::vector<unsigned int> CellularAutomataSpace::getSize(const unsigned int n) const
{
	std::vector<unsigned int> size;
	if (n == 0)
	{
		size.push_back(m);
		size.push_back(n);
		size.push_back(o);
	}
	if (n == 1)
	{
		size.push_back(m);
	}
	if (n == 2)
	{
		size.push_back(n);
	}
	if (n == 3)
	{
		size.push_back(o);
	}
	return size;
}

void CellularAutomataSpace::setBoundaryContidion(BoundaryContidionTypes type)
{
	boundary_contidion = type;
}

void CellularAutomataSpace::constructSpace(unsigned int nm, unsigned int nn, unsigned int no)
{
	//Wymiar w ka�dj osi musi by� wi�kszy od 0
	if (nm > 0)	m = nm;
	else				m = 1;
	if (nn > 0)	n = nn;
	else				n = 1;
	if (no > 0)	o = no;
	else				o = 1;
	//Twoznie kom�rek
	cells = new unsigned int **[m];
	for (unsigned int i = 0; i < m; i++)
	{
		cells[i] = new unsigned int *[n];
		for (unsigned int j = 0; j < n; j++)
		{
			cells[i][j] = new unsigned int[o];
			for (unsigned int k = 0; k < o; k++)
			{
				cells[i][j][k] = 0;
			}
		}
	}
	nucleons_count = 0;
}

void CellularAutomataSpace::destroySpace()
{
	//Usuwanie kom�rek
	if (cells)
	{
		for (unsigned int i = 0; i < m; i++)
		{
			for (unsigned int j = 0; j < n; j++)
			{
				if (cells[i][j])
				{
					delete[] cells[i][j];
				}
			}
			if (cells[i])
			{
				delete[] cells[i];
			}
		}
		delete[] cells;
	}
}