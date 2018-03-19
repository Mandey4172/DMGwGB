#pragma once
class ColorGenerator
{
public:
	ColorGenerator();
	~ColorGenerator();

	void generate(int n);

	float ** colors;
	int colorCount;;
};

