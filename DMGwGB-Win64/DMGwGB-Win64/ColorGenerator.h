#pragma once
class ColorGenerator
{
public:
	ColorGenerator();
	~ColorGenerator();

	void generate(int n);

	double ** colors;
	int colorCount;;
};

