#pragma once

#include<vector>

class CRule
{
public:
	CRule();
	~CRule();

	unsigned int grain_count = 0;
	//Funkcja przejœcia
	virtual void step(unsigned int * cell, class std::vector<unsigned int> & neighborhood);
};

