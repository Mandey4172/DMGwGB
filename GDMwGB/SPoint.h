#pragma once

class SPoint
{
public:
	SPoint(int nx, int ny, int nz)
	{
		this->x = nx;
		this->y = ny;
		this->z = nz;
	};
	int x, y, z;
};