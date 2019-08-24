#pragma once

#include<vector>

//! CellularAutomataRule
/// <summary>
//	Class
/// </summary>

class CellularAutomataRule
{
public:
	CellularAutomataRule();
	~CellularAutomataRule();

	unsigned int grain_count = 0;
	//Funkcja przej�cia
	virtual void check(unsigned int * cell, class std::vector<unsigned int> & neighborhood);
};
