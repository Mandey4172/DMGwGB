#include "ColorGenerator.h"

#include <iostream>
#include <cstdio>
#include <ctime>


ColorGenerator::ColorGenerator()
{
}


ColorGenerator::~ColorGenerator()
{
}

void ColorGenerator::generate(int n)
{
	colorCount = n;
	colors = new double *[n];

	for (int i = 0; i < floor(n / 2); ++i)
	{
		int r = rand() % 255,
			g = rand() % 255,
			b = rand() % 255;
		if ((r == 0) && (g == 0) && (b == 0))
		{
			--i;
			continue;
		}

		for (int j = 0; j < (i - i); j++)
		{
			if ((abs(colors[i][0] - r) < 10) &&
				(abs(colors[i][1] - g) < 10) &&
				(abs(colors[i][2] - b) < 10))
			{
				--i;
				continue;
			}
		}
		colors[i] = new double[3]{ (float)(r % 100), (float)(g % 100),(float)(155 + (b % 150)) };
	}
	for (int i = static_cast<int>(floor(n / 2)); i < n; ++i)
	{
		int r = rand() % 255,
			g = rand() % 255,
			b = rand() % 255;
		if ((r == 0) && (g == 0) && (b == 0))
		{
			--i;
			continue;
		}

		for (int j = 0; j < (i - i); j++)
		{
			if ((abs(colors[i][0] - r) < 10) &&
				(abs(colors[i][1] - g) < 10) &&
				(abs(colors[i][2] - b) < 10))
			{
				--i;
				continue;
			}
		}
		colors[i] = colors[i] = new double[3] { (float)(155 + (r % 100)), (float)(g % 80), (float)(b % 80)};
	}


	colors[0] = new double[3] {255.f, 255.f, 255.f};

	for (int i = 0; i < n; i++)
	{
		colors[i][0] /= 255;
		colors[i][1] /= 255;
		colors[i][2] /= 255;
	}
}
