#include "NucleonGenerator.h"
#include "CellularAutomata.h"

#include<vector>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

NucleonGenerator::NucleonGenerator()
{
}


NucleonGenerator::~NucleonGenerator()
{
}

void NucleonGenerator::random(CellularAutomata * ca,  int quantity)
{
	srand((unsigned)time(NULL));
	srand((unsigned)time(NULL));
	int * seed_x = new int[quantity];
	int * seed_y = new int[quantity];
	int * seed_z = new int[quantity];
	ca->nucleons_count = 0;
	for (int i = 0; i <= quantity; i++)
	{
		seed_x[i] = rand() % ca->getSize()[0];
		seed_y[i] = rand() % ca->getSize()[1];
		seed_z[i] = rand() % ca->getSize()[2];

		for (int j = 0; j < i; j++)
		{
			if ((seed_x[i] == seed_x[j]) && (seed_y[i] == seed_y[j]) && (seed_z[i] == seed_z[j]))
			{
				i--;
				break;
			}
		}
	}
	for (int i = 0; i < quantity; i++)
	{
		int x = seed_x[i],
			y = seed_y[i],
			z = seed_z[i];
		ca->getCells()[x][y][z] = ca->nucleons_count + 1 ;
		ca->nucleons_count++;
		//this->tool->select(world, x, y, z);
	}
}

void NucleonGenerator::random(CellularAutomata * ca,  int quantity, int r)
{
	srand((unsigned)time(NULL));
	int * seed_x = new int[quantity];
	int * seed_y = new int[quantity];
	int * seed_z = new int[quantity];

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
		seed_x[i] = rand() % ca->getSize()[0];
		seed_y[i] = rand() % ca->getSize()[1];
		seed_z[i] = rand() % ca->getSize()[2];

		for (int j = 0; j < i; j++)
		{
			int ri = round(sqrt(pow(abs(seed_x[i] - seed_x[j]), 2) + pow(abs(seed_y[i] - seed_y[j]), 2) + pow(abs(seed_z[i] - seed_z[j]), 2)));
			if (ri < r)
			{
				--i;
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
		ca->getCells()[x][y][z] = ca->nucleons_count + 1;
		ca->nucleons_count++;
		//this->tool->select(world, x, y, z);
	}
}

void NucleonGenerator::regular(CellularAutomata * ca, int quantity_m, int quantity_n, int quantity_o)
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
				ca->getCells()[x][y][z] = ca->nucleons_count + 1;
				ca->nucleons_count++;
			}
		}
	}
}

void NucleonGenerator::regular(CellularAutomata * ca, int quantity_n_m)
{
	this->regular(ca, quantity_n_m, quantity_n_m, quantity_n_m);
}

void NucleonGenerator::gradientA(CellularAutomata * ca, int cuts, int delta, int begin, short direction)
{

}
