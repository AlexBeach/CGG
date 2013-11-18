#include "cgg/Graphics.h"
#include <iostream>

// global time value (since program started)
float g_time = 0;

//------------------------------------------------------------------------------------------------------------------------------------
// called when we initialise the app
//------------------------------------------------------------------------------------------------------------------------------------
void init()
{
	// sets the size of the 2D screen coordinates. I'm just initialising the defaults here. You can use whatever you want!
	// args are: minx, maxx, miny, maxy
	setScreenCoordinates(-20.0f, 20.0f, -15.0f, 15.0f);

	// setting the background colour to a default grey!
	setBackgroundColour(0.6f, 0.6f, 0.7f);
}

//------------------------------------------------------------------------------------------------------------------------------------
// called when we need to update the app. 'dt' is the time delta (the number of seconds since the last frame)
//------------------------------------------------------------------------------------------------------------------------------------
void update(float dt)
{
	g_time += dt;
}

//------------------------------------------------------------------------------------------------------------------------------------
// generates a plane using parametric values 'u' and 'v'
//------------------------------------------------------------------------------------------------------------------------------------
void drawParametricSurface()
{
	// the min/max parametric values for the surface
	float umin = -12.0f;
	float umax =  12.0f;
	float vmin = -12.0f;
	float vmax =  12.0f;

	for(float u = umin; u <= umax; u += 0.05f)
	{
		for(float v = vmin; v <= vmax; v += 0.05f)
		{
			Vec3 P;
			P.x = u;
			P.z = v;
			P.y = 0;
			drawPoint(P);
		}
	}
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

	// draws te plane
	setColour(0.25f, 0.25f, 1.0f);
	drawParametricSurface();
}

//------------------------------------------------------------------------------------------------------------------------------------
// Called after draw3D. Allows you to draw a 2D overlay.
//------------------------------------------------------------------------------------------------------------------------------------
void draw()
{
	// draw something in 2D just so you can see it does actually work!
	setColour(0.1f, 0.1f, 0.9f);
	Vec2 topLeft(-19.5f, 14.5f);
	Vec2 topRight(19.5f, 14.5f);
	Vec2 bottomLeft(-19.5f, -14.5f);
	Vec2 bottomRight(19.5f, -14.5f);
	drawLine(topLeft, topRight);
	drawLine(topRight, bottomRight);
	drawLine(bottomRight, bottomLeft);
	drawLine(bottomLeft, topLeft);
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
