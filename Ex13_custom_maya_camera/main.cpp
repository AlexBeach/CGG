#include "cgg/Graphics.h"
#include <iostream>

//------------------------------------------------------------------------------------------------------------------------------------
// This example disables the internal maya camera controls (via the call to disableMayaCamera()), and implements it's own maya camera.
// The code is the same as that used internally, so it's possibly a bit pointless! This may be useful if you want to implement your
// own camera controller (e.g. the camera for a first person shooter). 
//------------------------------------------------------------------------------------------------------------------------------------

// These are the variables for my (terrible) maya camera
float g_zoom = 15.0f;
float g_rotx = 0;
float g_roty = 0.001f;
float g_tx = 0;
float g_ty = 0;
int g_lastx=0;
int g_lasty=0;
bool g_buttons[3] = {false, false, false};
bool g_rotating = false;

//------------------------------------------------------------------------------------------------------------------------------------
// called when we initialise the app
//------------------------------------------------------------------------------------------------------------------------------------
void init()
{
	// setting the background colour to a default grey!
	setBackgroundColour(0.6f, 0.6f, 0.7f);

	// turn off the internal maya camera (so we can use our own camera controls in 3D)
	disableMayaCamera();
}

//------------------------------------------------------------------------------------------------------------------------------------
// called when we need to update the app. 'dt' is the time delta (the number of seconds since the last frame)
//------------------------------------------------------------------------------------------------------------------------------------
void update(float /*dt*/)
{
}

//------------------------------------------------------------------------------------------------------------------------------------
// called when we want to draw the 3D data in our app.
//------------------------------------------------------------------------------------------------------------------------------------
void draw3D()
{
	const float DEG_TO_RAD = PI / 180.0f;
	const Vec3 xAxis(1.0f, 0, 0);
	const Vec3 yAxis(0, 1.0f, 0);

	translate(0, 0, -g_zoom);
	translate(g_tx, g_ty, 0);
	rotate(g_rotx * DEG_TO_RAD, xAxis);
	rotate(g_roty * DEG_TO_RAD, yAxis);

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
void mousePress(int button, int x, int y)
{
	// store button state
	g_buttons[button] = true;

	// if alt is held
	if(isAltPressed())
	{
		// we are rotating!
		g_rotating = true;

		// store last mouse pos
		g_lastx = x;
		g_lasty = y;
	}
	else
	{
		// we're not rotating.... 
	}
}

//------------------------------------------------------------------------------------------------------------------------------------
/// called when the left mouse button is released
//------------------------------------------------------------------------------------------------------------------------------------
void mouseRelease(int button, int /*x*/, int /*y*/)
{
	// store button state
	g_buttons[button] = false;

	if(g_rotating)
	{
		// disable the camera when all buttons have been released
		g_rotating = g_buttons[0] || g_buttons[1] || g_buttons[2];
	}
}

//------------------------------------------------------------------------------------------------------------------------------------
/// called when the mouse is moved (and the left button is held)
//------------------------------------------------------------------------------------------------------------------------------------
void mouseMove(int x, int y)
{
	// if the maya camera is enabled...
	if(g_rotating)
	{
		int diffx = x - g_lastx;
		int diffy = y - g_lasty;
		g_lastx = x;
		g_lasty = y;
		if(g_buttons[2] || (g_buttons[0] && g_buttons[1]))
		{
			g_zoom -= (float) 0.05f * diffx;
		}
		else
		if(g_buttons[0])
		{
			g_rotx -= (float) 0.5f * diffy;
			g_roty += (float) 0.5f * diffx;
		}
		else
		if(g_buttons[1])
		{
			g_tx += (float) 0.05f * diffx;
			g_ty += (float) 0.05f * diffy;
		}
	}
	else
	{
		// otherwise do something else
	}
}

//------------------------------------------------------------------------------------------------------------------------------------
/// main  \o/
//------------------------------------------------------------------------------------------------------------------------------------
int main()
{
	// just run the app.... 
	return runApp();
}
