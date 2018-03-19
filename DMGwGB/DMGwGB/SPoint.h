#pragma once

class SPoint
{
public:
	SPoint()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	SPoint(int nx, int ny, int nz)
	{
		this->x = nx;
		this->y = ny;
		this->z = nz;
	};
	SPoint(SPoint & np)
	{
		this->x = np.x;
		this->y = np.y;
		this->z = np.z;
	}
	int x, y, z;
};