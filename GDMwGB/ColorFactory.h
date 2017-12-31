#pragma once

#include<GL\glew.h>

namespace GDMwGB
{
	class Color
	{
	public:
		Color() { this->r = 1; this->g = 1; this->b = 1; this->alpha = 1; };
		Color(GLclampd  nr, GLclampd ng, GLclampd nb) { this->r = nr; this->g = ng; this->b = nb; this->alpha = 1; };
		GLclampd r;
		GLclampd g;
		GLclampd b;
		GLclampd alpha;
	};

	class ColorFactory
	{
	public:
		static Color * colors;
		static int count;
		static void generate(int i);
	};
}

