#include "Mouse.h"



Mouse::Mouse()
{
	mouseIsPressed = false;
	lastX = 0;
	lastY = 0;
}

bool Mouse::isPressed()
{
	return mouseIsPressed;
}

void Mouse::setPressed(bool nMouseIsPressed)
{
	mouseIsPressed = nMouseIsPressed;
}

void Mouse::setLastX(int x)
{
	lastX = x;
}

int Mouse::getLastX()
{
	return lastX;
}

void Mouse::setLastY(int y)
{
	lastY = y;
}

int Mouse::getLastY()
{
	return lastY;
}
