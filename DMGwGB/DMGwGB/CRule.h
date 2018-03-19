#pragma once

#include<vector>

class CRule
{
public:
	CRule();
	~CRule();

	int grain_count = 0;

	virtual void step(unsigned short * cell, class std::vector<unsigned short> neighborhood);
};

