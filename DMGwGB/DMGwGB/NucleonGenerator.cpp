#include "NucleonGenerator.h"
#include "CellularAutomataSpace.h"

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

void NucleonGenerator::random(const std::shared_ptr< CellularAutomataSpace > & ca, const unsigned int quantity) const
{
	std::vector<unsigned int> seed_x;
	std::vector<unsigned int> seed_y;
	std::vector<unsigned int> seed_z;

	int limit = 1000;
	for (unsigned int i = 0; i < quantity; i++)
	{
		const unsigned int m = ca->getSizeOnXAxis();
		const unsigned int n = ca->getSizeOnYAxis();
		const unsigned int o = ca->getSizeOnZAxis();

		seed_x.push_back(rand() % m);
		seed_y.push_back(rand() % n);
		seed_z.push_back(rand() % o);
		if (limit == 0) break;
		for (unsigned int j = 0; j < i; j++)
		{
			if ((seed_x.at(i) == seed_x.at(j)) && (seed_y.at(i) == seed_y.at(j)) && (seed_z.at(i) == seed_z.at(j)))
			{
				i--;
				seed_x.pop_back();
				seed_y.pop_back();
				seed_z.pop_back();
				limit--;
				break;
			}
		}
	}
	for (unsigned int i = 0; i < seed_x.size(); i++)
	{
		const unsigned int	x = seed_x.at(i),
							y = seed_y.at(i),
							z = seed_z.at(i);

		const unsigned int nucleonsCount = ca->getNucleonsCount() + i;
		ca->getCells()[x][y][z] = nucleonsCount + 1;
	}
	ca->setNucleonsCount(ca->getNucleonsCount() + static_cast<unsigned int>(seed_x.size()));
}

void NucleonGenerator::random(const std::shared_ptr< CellularAutomataSpace > & ca, unsigned int quantity, unsigned int r) const
{
	std::vector<unsigned int> seed_x;
	std::vector<unsigned int> seed_y;
	std::vector<unsigned int> seed_z;

	int limit = 1000;
	unsigned int seeds = 0;

	for (unsigned int i = 0; i < quantity; i++)
	{
		bool success = true;

		const unsigned int m = ca->getSizeOnXAxis();
		const unsigned int n = ca->getSizeOnYAxis();
		const unsigned int o = ca->getSizeOnZAxis();

		if (limit <= 0)
		{
			break;
		}
		limit--;

		seed_x.push_back(rand() % m);
		seed_y.push_back(rand() % n);
		seed_z.push_back(rand() % o);

		for (unsigned int j = 0; j < i; j++)
		{
			unsigned int ri = static_cast<unsigned int>(
				round(sqrt(pow(abs(static_cast<int>(seed_x.at(i) - seed_x.at(j))), 2) +
					pow(abs(static_cast<int>(seed_y.at(i) - seed_y.at(j))), 2) +
					pow(abs(static_cast<int>(seed_z.at(i) - seed_z.at(j))), 2))));
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
	for (unsigned int i = 0; i < seeds; i++)
	{
		const unsigned int	x = seed_x.at(i),
							y = seed_y.at(i),
							z = seed_z.at(i);

		const unsigned int count = ca->getNucleonsCount() + i;
		ca->getCells()[x][y][z] = count + 1;
	}
	ca->setNucleonsCount(ca->getNucleonsCount() + static_cast<unsigned int>(seed_x.size()));
}

void NucleonGenerator::regular(const std::shared_ptr< CellularAutomataSpace > & ca, unsigned int quantity_m, unsigned int quantity_n, unsigned int quantity_o) const
{
	int m = static_cast<int>(ca->getSizeOnXAxis()),
		n = static_cast<int>(ca->getSizeOnYAxis()),
		o = static_cast<int>(ca->getSizeOnZAxis());
	int step_x = m / (quantity_m + 1),
		step_y = n / (quantity_n + 1),
		step_z = o / (quantity_o + 1);

	int	rest_x = static_cast<int>(floor((m - (step_x * (quantity_m + 1))) / 2)),
		rest_y = static_cast<int>(floor((n - (step_y * (quantity_n + 1))) / 2)),
		rest_z = static_cast<int>(floor((o - (step_z * (quantity_o + 1))) / 2));

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

	for (unsigned int i = 1; i < (quantity_m + 1); i++)
	{
		for (unsigned int j = 1; j < (quantity_n + 1); j++)
		{
			for (unsigned int k = 1; k < (quantity_o + 1); k++)
			{
				int x = rest_x + (i * step_x),
					y = rest_y + (j * step_y),
					z = rest_z + (k * step_z);
				if (x >= 0 && x < m &&
					y >= 0 && y < n &&
					z >= 0 && z < o)
				{
					const unsigned int nucleonsCount = ca->getNucleonsCount() + i;
					ca->getCells()[x][y][z] = nucleonsCount + 1;
					ca->setNucleonsCount(ca->getNucleonsCount() + 1);
				}
			}
		}
	}
}

void NucleonGenerator::regular(const std::shared_ptr< CellularAutomataSpace > & ca, unsigned int quantity_n_m_o) const
{
	regular(ca, quantity_n_m_o, quantity_n_m_o, quantity_n_m_o);
}
