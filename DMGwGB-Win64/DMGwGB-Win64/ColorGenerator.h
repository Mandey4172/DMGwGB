#pragma once

#include <vector>
#include <array>
class ColorGenerator
{
public:
	ColorGenerator();
	~ColorGenerator();

	void generate(int n);

	float ** colors;
	unsigned int colorCount;
};

