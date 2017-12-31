#include "ColorFactory.h"

#include <iostream>
#include <cstdio>
#include <ctime>

using namespace GDMwGB;

GDMwGB::Color * GDMwGB::ColorFactory::colors = new Color(0, 0, 0);
int GDMwGB::ColorFactory::count = 1;

void GDMwGB::ColorFactory::generate(int n)
{
	GDMwGB::ColorFactory::count = n;
	GDMwGB::ColorFactory::colors = new GDMwGB::Color[n];

	for (int i = 0; i < floor(n/2); ++i)
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
			if ((abs(colors[i].r - r) < 10) &&
				(abs(colors[i].g - g) < 10) &&
				(abs(colors[i].b - b) < 10))
			{
				--i;
				continue;
			}
		}
		colors[i] = GDMwGB::Color(r % 50, g % 50, 155 + (b % 150));
	}
	for (int i = floor(n / 2); i < n; ++i)
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
			if ((abs(colors[i].r - r) < 10) &&
				(abs(colors[i].g - g) < 10) &&
				(abs(colors[i].b - b) < 10))
			{
				--i;
				continue;
			}
		}
		colors[i] = GDMwGB::Color(155 + (r % 100),g % 80, b % 80);
	}
	

	GDMwGB::ColorFactory::colors[0] = GDMwGB::Color(255, 255, 255);
	GDMwGB::ColorFactory::colors[1] = GDMwGB::Color(20, 20, 20);

	for (int i = 0; i < n; ++i)
	{
		colors[i].r /= 255;
		colors[i].g /= 255;
		colors[i].b /= 255;
	}
}


//void GDMwGB::ColorFactory::generate(int n)
//{
//	GDMwGB::ColorFactory::count = n;
//	GDMwGB::ColorFactory::colors = new GDMwGB::Color[n];
//	for (int i = 0; i < n; ++i)
//	{
//		int r = rand() % 255,
//			g = rand() % 255,
//			b = rand() % 255;
//		if ((r == 0) && (g == 0) && (b == 0))
//		{
//			--i;
//			continue;
//		}
//
//		for (int j = 0; j < (i - i); j++)
//		{
//			if ((abs(colors[i].r - r) < 10) &&
//				(abs(colors[i].g - g) < 10) &&
//				(abs(colors[i].b - b) < 10))
//			{
//				--i;
//				continue;
//			}
//		}
//		colors[i] = GDMwGB::Color(r % 150, g % 150, 135 + (b % 120));
//	}
//	GDMwGB::ColorFactory::colors[0] = GDMwGB::Color(255, 255, 255);
//	GDMwGB::ColorFactory::colors[1] = GDMwGB::Color(20, 20, 20);
//	for (int i = 0; i < n; ++i)
//	{
//		colors[i].r /= 255;
//		colors[i].g /= 255;
//		colors[i].b /= 255;
//	}
//}