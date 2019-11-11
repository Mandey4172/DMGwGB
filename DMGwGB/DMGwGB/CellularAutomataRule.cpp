#include "CellularAutomataRule.h"

CellularAutomataRule::CellularAutomataRule(const CellularAutomataRule& other)
{
	grain_count = other.grain_count;
}

CellularAutomataRule::CellularAutomataRule(CellularAutomataRule&& other)
{
	std::swap(grain_count, other.grain_count);
}

CellularAutomataRule& CellularAutomataRule::operator=(const CellularAutomataRule& other)
{
	grain_count = other.grain_count;
	return *this;
}

CellularAutomataRule& CellularAutomataRule::operator=(CellularAutomataRule&& other)
{
	std::swap(grain_count, other.grain_count);
	return *this;
}

CellularAutomataRule::~CellularAutomataRule()
{
}
