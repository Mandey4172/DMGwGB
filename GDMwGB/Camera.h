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

private:
	float scale;
	float alpha;
	float beta;
};

