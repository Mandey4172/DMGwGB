#include"CellularAutomata.h"
#include"CellularAutomataSpace.h"
#include "CellularAutomataRule.h"
#include"Neighborhood.h"
#include"MooreNeighborhood.h"
#include"VonNeummanNeighborhood.h"
#include"PentagonalNeighborhood.h"
#include"HexagonalNeighborhood.h"

#include<vector>

CellularAutomata::CellularAutomata() noexcept :
	cellular_automata_space(nullptr),
	neighborhood(nullptr),
	rule(nullptr)	
{}

CellularAutomata::CellularAutomata(const CellularAutomata & other)
{
	cellular_automata_space = other.cellular_automata_space;
	neighborhood = other.neighborhood;
	rule = other.rule;
}

CellularAutomata::CellularAutomata(CellularAutomata&& other) noexcept
{
	std::swap(cellular_automata_space, other.cellular_automata_space);
	std::swap(neighborhood, other.neighborhood);
	std::swap(rule, other.rule);
}

CellularAutomata& CellularAutomata::operator=(const CellularAutomata& other)
{
	cellular_automata_space = other.cellular_automata_space;
	neighborhood = other.neighborhood;
	rule = other.rule;
}

CellularAutomata& CellularAutomata::operator=(CellularAutomata&& other) noexcept
{
	std::swap(cellular_automata_space, other.cellular_automata_space);
	std::swap(neighborhood, other.neighborhood);
	std::swap(rule, other.rule);
}

CellularAutomata::~CellularAutomata() {}

bool CellularAutomata::step() 
{ 
	return true; 
}

void CellularAutomata::start()
{
	while (!step());
}

void CellularAutomata::setCellularAutomataSpace(const std::shared_ptr<class CellularAutomataSpace>& new_cellularautomata)
{
	cellular_automata_space = new_cellularautomata;
}

std::shared_ptr<class CellularAutomataSpace> CellularAutomata::getCellularAutomataSpace() const
{
	return cellular_automata_space;
}

void CellularAutomata::setNeighborhood(const std::shared_ptr<class Neighborhood>& new_neighborhood)
{
	neighborhood = new_neighborhood;
}

std::shared_ptr<class Neighborhood> CellularAutomata::getNeighborhood() const
{
	return neighborhood;
}

void CellularAutomata::setCellularAutomataRule(const std::shared_ptr<class CellularAutomataRule>& new_rule)
{
	rule = new_rule;
}

std::shared_ptr<class CellularAutomataRule> CellularAutomata::getCellularAutomataRule() const
{
	return rule;
}