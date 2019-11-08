#pragma once

#include<vector>

//! CellularAutomataRule
/// <summary>
//	Class
/// </summary>

class CellularAutomataRule
{
public:
	CellularAutomataRule() {};
	virtual ~CellularAutomataRule() {};

	/// <summary> Transition function performed on cell. Modyfies cells state to the next time step </summary>
	virtual void transition(unsigned int * cell, class std::vector<unsigned int> & neighborhood) = 0;

	/// <summary> Transition function performed on cell. Modyfies cells state to the next time step </summary>
	void setGrainCount(unsigned int count) { grain_count = count; }

protected:
	unsigned int grain_count = 0;
};
