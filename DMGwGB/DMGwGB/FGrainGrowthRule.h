#pragma once

#include<unordered_set>
#include<array>
#include<list>
#include<xhash>

#include "CRule.h"
#include "SPoint.h"



class FGrainGrowthRule :
	public CRule
{
public:
	FGrainGrowthRule();
	~FGrainGrowthRule();
	//typedef
	std::list<std::array<int, 3>> queue;

	virtual void step(unsigned int * cell, class std::vector<unsigned int> neighborhood);
};

