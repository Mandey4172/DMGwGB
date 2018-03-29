#pragma once

#include<unordered_set>
#include<array>
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
	std::vector<std::array<int, 3>> queue;

	virtual void step(unsigned short * cell, class std::vector<unsigned short> neighborhood);
};

