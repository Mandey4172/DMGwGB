#pragma once

#include<vector>

class CRule
{
public:
	CRule();
	~CRule();

	int grain_count = 0;

	virtual void step(class Cell * cell, class std::vector<class Cell*> neighborhood);
};

