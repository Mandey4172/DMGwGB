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

CellularAutomataSpace::CellularAutomataSpace(unsigned int x, unsigned int y, unsigned int z) noexcept
	: cells(nullptr), 
	m(x), n(y), o(z), 
	boundary_contidion(BoundaryContidionTypes::Blocking), 
	nucleons_count(0)
{
	constructSpace(x,y,z);
}

CellularAutomataSpace::CellularAutomataSpace(const CellularAutomataSpace & ca)
{
	m = ca.m;
	n = ca.n;
	o = ca.o;

	cells = new unsigned int **[m];
	for (unsigned int i = 0; i < m; i++)
	{
		cells[i] = new unsigned int *[n];
		for (unsigned int j = 0; j < n; j++)
		{
			cells[i][j] = new unsigned int[o];
			for (unsigned int k = 0; k < o; k++)
			{
				cells[i][j][k] = ca.cells[i][j][k];
			}
			//std::copy(ca.cells[i][j], ca.cells[i][j] + o, cells[i][j]);
		}
	}
	nucleons_count = ca.nucleons_count;
	boundary_contidion = ca.boundary_contidion;
}

CellularAutomataSpace::CellularAutomataSpace(CellularAutomataSpace && ca) noexcept
{
	cells = ca.cells;
	m = ca.m;
	n = ca.n;
	o = ca.o;
	nucleons_count = ca.nucleons_count;
	boundary_contidion = ca.boundary_contidion;

	ca.m = 0;
	ca.n = 0;
	ca.o = 0;
	ca.cells = nullptr;
	ca.boundary_contidion = BoundaryContidionTypes::Blocking;
	ca.nucleons_count = 0;
}

CellularAutomataSpace& CellularAutomataSpace::operator=(const CellularAutomataSpace & ca)
{
	*this = CellularAutomataSpace(ca);
	return *this;
}

CellularAutomataSpace& CellularAutomataSpace::operator=(CellularAutomataSpace&& ca) noexcept
{
	std::swap(*this,ca);
	return *this;
}

CellularAutomataSpace::~CellularAutomataSpace()
{
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

std::string CellularAutomataSpace::save() const
{
	std::string save;
	const unsigned int size = 4 * m * n * o;

	save.reserve(size);
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

void CellularAutomataSpace::load(const std::string &path)
{
	struct CellStateChunk
	{
		CellStateChunk() : x(0), y(0), z(0), state(0) {};
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
		file.read(&data.at(0), data.size());
		file.close();

		std::vector<CellStateChunk> cell_chunks;
		unsigned int a = 0, b = 0, c = 0,
			smax = 0;
		{
			std::vector<std::string> data_chunks = split(data, "\n");
#pragma omp parallel for schedule(static)
			for (unsigned int i = 0; i < data_chunks.size(); i++)
			{
				std::string data_chunk = data_chunks.at(i);
				CellStateChunk cell_chunk;
				std::vector<std::string> string_chunk = split(data_chunk, " ");
				if (string_chunk.size() == 4)
				{
					cell_chunk.x = static_cast<unsigned int>(std::stoi(string_chunk.at(0)));
					if (cell_chunk.x > a) a = cell_chunk.x;
					cell_chunk.y = static_cast<unsigned int>(std::stoi(string_chunk.at(1)));
					if (cell_chunk.y > b) b = cell_chunk.y;
					cell_chunk.z = static_cast<unsigned int>(std::stoi(string_chunk.at(2)));
					if (cell_chunk.z > c) c = cell_chunk.z;
					cell_chunk.state = static_cast<unsigned int>(std::stoi(string_chunk.at(3)));
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
		for (unsigned int i = 0; i < cell_chunks.size(); i++)
		{
			CellStateChunk chunk = cell_chunks.at(i);
			cells[chunk.x][chunk.y][chunk.z] = chunk.state;
		}
	}
}

unsigned int *** CellularAutomataSpace::getCells() const
{
	return cells;
}

BoundaryContidionTypes CellularAutomataSpace::getBoundatyConditionType() const
{
	return boundary_contidion;
}

void CellularAutomataSpace::setBoundaryContidion(BoundaryContidionTypes type)
{
	boundary_contidion = type;
}

unsigned int CellularAutomataSpace::getNucleonsCount() const
{
	return nucleons_count;
}

void CellularAutomataSpace::setNucleonsCount(unsigned int count)
{
	nucleons_count = count;
}

unsigned int CellularAutomataSpace::getSizeOnXAxis() const
{
	return m;
}

unsigned int CellularAutomataSpace::getSizeOnYAxis() const
{
	return n;
}

unsigned int CellularAutomataSpace::getSizeOnZAxis() const
{
	return o;
}

void CellularAutomataSpace::constructSpace(unsigned int nm, unsigned int nn, unsigned int no)
{
	if (nm > 0)	m = nm;
	else				m = 1;
	if (nn > 0)	n = nn;
	else				n = 1;
	if (no > 0)	o = no;
	else				o = 1;
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