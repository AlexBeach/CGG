#include "cgg/Graphics.h"
#include <iostream>

float g_time = 0;

//------------------------------------------------------------------------------------------------------------------------------------
// called when we initialise the app
//------------------------------------------------------------------------------------------------------------------------------------
void init()
{
}

//------------------------------------------------------------------------------------------------------------------------------------
// called when we need to update the app. 'dt' is the time delta (the number of seconds since the last frame)
//------------------------------------------------------------------------------------------------------------------------------------
void update(float dt)
{
	g_time += dt;

	// when accessing the keys (either alphanumeric or standard symbols), you can just pass them in with single quotes....
	if(isKeyPressed('q'))  std::cout << "q" << std::endl; 
	if(isKeyPressed('<'))  std::cout << "<" << std::endl; 
	if(isKeyPressed('2'))  std::cout << "2" << std::endl; 

	// you might find it useful to test for both the lowercase and UPPERCASE version of the character (just in case Caps Lock is on!)
	if(isKeyPressed('w') || isKeyPressed('W')) std::cout << "w" << std::endl;

	// If you want to access other keys (i.e. ones that don't naturally map to a single character!), then you can use the following 
	// enum values (posh word for const integers!). 
	if(isKeyPressed(kKeyEnter)) std::cout << "kKeyEnter" << std::endl;
	if(isKeyPressed(kKeyBackSpace)) std::cout << "kKeyBackSpace" << std::endl;
	if(isKeyPressed(kKeyTab)) std::cout << "kKeyTab" << std::endl;
	if(isKeyPressed(kKeyEscape)) std::cout << "kKeyEscape" << std::endl;
	if(isKeyPressed(kKeyDelete)) std::cout << "kKeyDelete" << std::endl;
	if(isKeyPressed(kKeyF1)) std::cout << "kKeyF1" << std::endl;
	if(isKeyPressed(kKeyF2)) std::cout << "kKeyF2" << std::endl;
	if(isKeyPressed(kKeyF3)) std::cout << "kKeyF3" << std::endl;
	if(isKeyPressed(kKeyF4)) std::cout << "kKeyF4" << std::endl;
	if(isKeyPressed(kKeyF5)) std::cout << "kKeyF5" << std::endl;
	if(isKeyPressed(kKeyF6)) std::cout << "kKeyF6" << std::endl;
	if(isKeyPressed(kKeyF7)) std::cout << "kKeyF7" << std::endl;
	if(isKeyPressed(kKeyF8)) std::cout << "kKeyF8" << std::endl;
	if(isKeyPressed(kKeyF9)) std::cout << "kKeyF9" << std::endl;
	if(isKeyPressed(kKeyF10)) std::cout << "kKeyF10" << std::endl;
	if(isKeyPressed(kKeyF11)) std::cout << "kKeyF11" << std::endl;
	if(isKeyPressed(kKeyF12)) std::cout << "kKeyF12" << std::endl;
	if(isKeyPressed(kKeyLeft)) std::cout << "kKeyLeft" << std::endl;
	if(isKeyPressed(kKeyUp)) std::cout << "kKeyUp" << std::endl;
	if(isKeyPressed(kKeyRight)) std::cout << "kKeyRight" << std::endl;
	if(isKeyPressed(kKeyDown)) std::cout << "kKeyDown" << std::endl;
	if(isKeyPressed(kKeyPageUp)) std::cout << "kKeyPageUp" << std::endl;
	if(isKeyPressed(kKeyPageDown)) std::cout << "kKeyPageDown" << std::endl;
	if(isKeyPressed(kKeyHome)) std::cout << "kKeyHome" << std::endl;
	if(isKeyPressed(kKeyEnd)) std::cout << "kKeyEnd" << std::endl;
	if(isKeyPressed(kKeyInsert)) std::cout << "kKeyInsert" << std::endl;
}

//------------------------------------------------------------------------------------------------------------------------------------
// called when we want to draw the 3D data in our app.
//------------------------------------------------------------------------------------------------------------------------------------
void draw3D()
{
	// draw the grid on the floor
	setColour(0.25f, 0.25f, 0.25f);
	for(float i = -10.0f; i <= 10.1f; i += 1.0f)
	{
		Vec3 zmin(i, 0, -10);
		Vec3 zmax(i, 0,  10);
		Vec3 xmin(-10, 0, i);
		Vec3 xmax(10, 0, i);
		drawLine(xmin, xmax);
		drawLine(zmin, zmax);
	}
}

//------------------------------------------------------------------------------------------------------------------------------------
// called when we want to draw a 2D overlay
//------------------------------------------------------------------------------------------------------------------------------------
void draw()
{
}

//------------------------------------------------------------------------------------------------------------------------------------
/// called when the left mouse button is pressed
//------------------------------------------------------------------------------------------------------------------------------------
void mousePress(int x, int y)
{
	Vec2 p = getScreenCoordinates(x, y);
}

//------------------------------------------------------------------------------------------------------------------------------------
/// called when the left mouse button is released
//------------------------------------------------------------------------------------------------------------------------------------
void mouseRelease(int x, int y)
{
	Vec2 p = getScreenCoordinates(x, y);
}

//------------------------------------------------------------------------------------------------------------------------------------
/// called when the mouse is moved (and the left button is held)
//------------------------------------------------------------------------------------------------------------------------------------
void mouseMove(int x, int y)
{
	Vec2 p = getScreenCoordinates(x, y);
}

//------------------------------------------------------------------------------------------------------------------------------------
/// main  \o/
//------------------------------------------------------------------------------------------------------------------------------------
int main()
{
	// just run the app.... 
	return runApp();
}
