#pragma once
class Mouse
{
public:
	Mouse();
	
	bool isPressed();
	void setPressed(bool MouseIsPressed);

	void setLastX(int x);
	int	 getLastX();

	void setLastY(int y);
	int	 getLastY();

private:
	bool mouseIsPressed;
	int  lastX;
	int  lastY;
};

