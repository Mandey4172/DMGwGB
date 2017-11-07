#pragma once

#include<vector>

class CRule
{
public:
	CRule();
	~CRule();
	virtual void step(class Cell * cell, class std::vector<class Cell> neighborhood);
};

