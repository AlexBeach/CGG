#include "cgg/Graphics.h"
#include <vector>

// a dynamic array of points. You may not have seen this before! 
// Nothing to fear, it's just an array of Vec2's. Unlike normal C++ arrays, std::vector<> can be resized!
std::vector<Vec2> g_points;

// the current position of the mouse cursor when dragging 
Vec2 g_currPoint;

// are we dragging the mouse?
bool g_mouseIsDragging = false;

// a global time value (because it may be useful)
float g_time = 0;

//------------------------------------------------------------------------------------------------------------------------------------
// called when we initialise the app
//------------------------------------------------------------------------------------------------------------------------------------
void init()
{
	setWindowTitle("Click to add. Ctrl + Click to remove");
}

//------------------------------------------------------------------------------------------------------------------------------------
// called when we need to update the app. 'dt' is the time delta (the number of seconds since the last frame)
//------------------------------------------------------------------------------------------------------------------------------------
void update(float dt)
{
	g_time += dt;
}

//------------------------------------------------------------------------------------------------------------------------------------
// called when we want to draw the 3D data in our app.
//------------------------------------------------------------------------------------------------------------------------------------
void draw3D()
{
}

//------------------------------------------------------------------------------------------------------------------------------------
// called when we want to draw a 2D overlay
//------------------------------------------------------------------------------------------------------------------------------------
void draw()
{
	setColour(1.0f, 0.0f, 0.0f);

	// iterate over each element in the array
	for(size_t i = 0; i < g_points.size(); ++i)
	{
		drawPoint(g_points[i]);
	}

	// draw a little blue crosshair when we are dragging the mouse
	if(g_mouseIsDragging)
	{
		setColour(0.0f, 0.0f, 1.0f);
		Vec2 minx = g_currPoint - Vec2(0.5f, 0);
		Vec2 maxx = g_currPoint + Vec2(0.5f, 0);
		Vec2 miny = g_currPoint - Vec2(0, 0.5f);
		Vec2 maxy = g_currPoint + Vec2(0, 0.5f);
		drawLine(minx, maxx);
		drawLine(miny, maxy);
	}
}

//------------------------------------------------------------------------------------------------------------------------------------
/// called when the left mouse button is pressed
//------------------------------------------------------------------------------------------------------------------------------------
void mousePress(int x, int y)
{
	// convert the mouse click into screen coordinates
	Vec2 p = getScreenCoordinates(x, y);

	// There are a few 'meta' keys than can be recieved when a mouse click occurs. In this case, I'm just looking for control.
	// Shift is also available (isShiftPressed), as is Alt (isAltPressed). Currently mouse messages when alt is pressed are intercepted 
	// by my Maya camera code (so you wont be able to recieve them!). If you need these Alt+mouse messages, then you will have to disable 
	// the maya camera (i.e. call disableMayaCamera()).
	if(isCtrlPressed())
	{
		// and we have some points in the array
		if(g_points.size())
		{
			// remove the last point
			g_points.pop_back();
		}
	}
	else
	{
		// otherwise, store the current point
		g_currPoint = p;

		// and set a flag to make sure we know we're dragging
		g_mouseIsDragging = true;
	}
}

//------------------------------------------------------------------------------------------------------------------------------------
/// called when the left mouse button is released
//------------------------------------------------------------------------------------------------------------------------------------
void mouseRelease(int x, int y)
{
	Vec2 p = getScreenCoordinates(x, y);

	// when the mouse is released, if we are dragging the mouse...
	if(g_mouseIsDragging)
	{
		// add the point to the back of the point array
		g_points.push_back(p);

		// turn off dragging
		g_mouseIsDragging = false;
	}
}

//------------------------------------------------------------------------------------------------------------------------------------
/// called when the mouse is moved (and the left button is held)
//------------------------------------------------------------------------------------------------------------------------------------
void mouseMove(int x, int y)
{
	Vec2 p = getScreenCoordinates(x, y);

	// if dragging...
	if(g_mouseIsDragging)
	{
		// update current position
		g_currPoint = p;
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
