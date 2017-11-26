#pragma once
class Camera
{
public:
	Camera();
	~Camera();

	float	getAlphaRotation();
	void	setAlphaRotation( float AlphaRotation );

	float	getBetaRotation();
	void	setBetaRotation( float BetaRotation );

	float	getScale();
	void	setScale( float Scale );

	int x0, x1,
		y0, y1,
		z0, z1;

private:
	float scale;
	float alpha;
	float beta;
};

