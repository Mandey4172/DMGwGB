#include "NucleonGenerator.h"
#include "CellularAutomata.h"

#include<vector>
#include<array>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

NucleonGenerator::NucleonGenerator()
{
	srand((unsigned)time(NULL));
}


NucleonGenerator::~NucleonGenerator()
{
}

void NucleonGenerator::random(CellularAutomata * ca,const unsigned int quantity, unsigned int grain_count)
{
	std::vector<unsigned int> seed_x;
	std::vector<unsigned int> seed_y;
	std::vector<unsigned int> seed_z;

	ca->nucleons_count = 0;

	for (int i = 0; i < quantity; i++)
	{
		seed_x.push_back(rand() % ca->getSize()[0]);
		seed_y.push_back(rand() % ca->getSize()[1]);
		seed_z.push_back(rand() % ca->getSize()[2]);

		for (int j = 0; j < i; j++)
		{
			if ((seed_x[i] == seed_x[j]) && (seed_y[i] == seed_y[j]) && (seed_z[i] == seed_z[j]))
			{
				i--;
				seed_x.pop_back();
				seed_y.pop_back();
				seed_z.pop_back();
				break;
			}
		}
	}
	for (int i = 0; i < seed_x.size(); i++)
	{
		int x = seed_x[i],
			y = seed_y[i],
			z = seed_z[i];
		ca->getCells()[x][y][z] = (ca->nucleons_count + 1);
		ca->nucleons_count++;
	}
}

void NucleonGenerator::random(CellularAutomata * ca, unsigned int quantity, unsigned int grain_count, unsigned int r)
{
	std::vector<unsigned int> seed_x;
	std::vector<unsigned int> seed_y;
	std::vector<unsigned int> seed_z;

	int limit = 1000;
	int seeds = 0;

	for (int i = 0; i < quantity; i++)
	{
		bool success = true;

		if (limit <= 0)
		{
			break;
		}
		limit--;
		seed_x.push_back(rand() % ca->getSize()[0]);
		seed_y.push_back(rand() % ca->getSize()[1]);
		seed_z.push_back(rand() % ca->getSize()[2]);

		for (int j = 0; j < i; j++)
		{
			int ri = round(sqrt(pow( abs( static_cast<int>( seed_x[i] - seed_x[j])), 2) +
								pow( abs( static_cast<int>( seed_y[i] - seed_y[j])), 2) +
								pow( abs( static_cast<int>( seed_z[i] - seed_z[j])), 2)));
			if (ri < r)
			{
				--i;
				seed_x.pop_back();
				seed_y.pop_back();
				seed_z.pop_back();
				success = false;
				break;
			}
		}
		if (success)
		{
			seeds++;
		}
	}
	for (int i = 0; i < seeds; i++)
	{
		int x = seed_x[i],
			y = seed_y[i],
			z = seed_z[i];
		ca->getCells()[x][y][z] = (ca->nucleons_count + 1) % grain_count;
		ca->nucleons_count++;
		//this->tool->select(world, x, y, z);
	}
}

void NucleonGenerator::regular(CellularAutomata * ca, unsigned int quantity_m, unsigned int quantity_n, unsigned int quantity_o, unsigned int grain_count)
{
	int step_x = ca->getSize()[0] / (quantity_m + 1),
		step_y = ca->getSize()[1] / (quantity_n + 1),
		step_z = ca->getSize()[2] / (quantity_o + 1),
		rest_x = floor((ca->getSize()[0] - (step_x * (quantity_m + 1))) / 2),
		rest_y = floor((ca->getSize()[1] - (step_y * (quantity_n + 1))) / 2),
		rest_z = floor((ca->getSize()[2] - (step_z * (quantity_o + 1))) / 2);

	if (step_x < 1)
	{
		step_x = 1;
	}
	if (step_y < 1)
	{
		step_y = 1;
	}
	if (step_z < 1)
	{
		step_z = 1;
	}
	int counter = 0;
	for (int i = 1; i < (quantity_n + 1); i++)
	{
		for (int j = 1; j < (quantity_m + 1); j++)
		{
			for (int k = 1; k < (quantity_o + 1); k++)
			{
				int x = rest_x + (i * step_x),
					y = rest_y + (j * step_y),
					z = rest_z + (k * step_z);
				ca->getCells()[x][y][z] = (ca->nucleons_count + 1) % grain_count;
				ca->nucleons_count++;
			}
		}
	}
}

void NucleonGenerator::regular(CellularAutomata * ca, unsigned int quantity_n_m_o, unsigned int grain_count)
{
	this->regular(ca, quantity_n_m_o, quantity_n_m_o, quantity_n_m_o, grain_count);
}

void NucleonGenerator::gradientA(CellularAutomata * ca, unsigned int grain_count, unsigned int cuts, unsigned int delta, unsigned int begin, short direction)
{
}

