#pragma once

#include<vector>

class CRule
{
public:
	CRule();
	~CRule();

	unsigned int grain_count = 0;
	//Funkcja przej�cia
	virtual void step(unsigned int * cell, class std::vector<unsigned int> & neighborhood);
};

