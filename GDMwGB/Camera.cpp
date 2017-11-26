#include "Camera.h"

Camera::Camera()
{
	alpha	= 0.f;
	beta	= 0.f;
	scale	= 10.f;
	x0 = 0;
	x1 = 0;
	y0 = 0;
	y1 = 0;
	z0 = 0;
	z1 = 0;
}

Camera::~Camera()
{
}

float Camera::getAlphaRotation()
{
	return alpha;
}

void Camera::setAlphaRotation(float AlphaRotation)
{
	if (AlphaRotation >= 0.f && AlphaRotation < 360.f)
	{
		alpha = AlphaRotation;
	}
	else if (AlphaRotation < 0.f)
	{
		alpha = 359.99f;
	}
	else if (AlphaRotation >= 360.f)
	{
		alpha = 0.f;
	}
}

float Camera::getBetaRotation()
{
	return beta;
}

void Camera::setBetaRotation(float BetaRotation)
{
	if (BetaRotation >= -90.f && BetaRotation < 90.f)
	{
		beta = BetaRotation;
	}
	else if (BetaRotation < -90.f)
	{
		beta = -90.f;
	}
	else if (BetaRotation >= 90.f)
	{
		beta = 89.99f;
	}
}

float Camera::getScale()
{
	return scale;
}

void Camera::setScale(float Scale)
{
	if (Scale >= 1.f && Scale < 100.f)
	{
		scale = Scale;
	}
	else if (Scale < 1.f)
	{
		scale = 1.f;
	}
	else if (Scale >= 90.f)
	{
		scale = 99.99f;
	}
}
