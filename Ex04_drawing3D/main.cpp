#include "cgg/Graphics.h"
#include <iostream>

float g_time = 0;

int g_circle = 0;
int g_square = 0;
int g_lineStrip = 0;
int g_lines = 0;

//------------------------------------------------------------------------------------------------------------------------------------
// called when we initialise the app
//------------------------------------------------------------------------------------------------------------------------------------
void init()
{
	// construct a circle from points
	{
		g_circle = beginShape();
		for(float angle = -PI; angle <= PI; angle += 0.2)
		{
			Vec3 p(cos(angle), sin(angle), -2.0f);
			drawPoint(p);
		}
		endShape();
	}

	// construct a square from a line loop
	{
		g_square = beginShape();
		Vec3 points[] = 
		{
			Vec3(-1.0f, 1.0f, -2.0f), 
			Vec3( 1.0f, 1.0f, -2.0f), 
			Vec3( 1.0f,-1.0f, -2.0f), 
			Vec3(-1.0f,-1.0f, -2.0f)
		};
		drawLineLoop(points, 4);
		endShape();
	}

	// construct a line strip
	{
		g_lineStrip = beginShape();
		Vec3 points[] = 
		{
			Vec3(1.0f, 1.0f, -2.0f),
			Vec3(0.8f,-1.0f, -2.0f),
			Vec3(-0.8f,-1.0f, -2.0f),
			Vec3(-1.0f, 1.0f, -2.0f)
		};
		drawLineStrip(points, 4);
		endShape();
	}

	// construct a little cross
	{
		g_lines = beginShape();
		drawLine(Vec3(-1.0f, 0, -2.0f), Vec3(1.0f, 0, -2.0f));
		drawLine(Vec3(0, -1.0f, -2.0f), Vec3(0, 1.0f, -2.0f));
		endShape();
	}
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

	setColour(1.0f, 1.0f, 1.0f);

	// draw all of the shapes using nice and efficient display lists... :)
	Matrix3 matrix;
	matrix.w.x = -10.0f;
	drawShape(matrix, g_circle);
	matrix.w.x = -5.0f;
	drawShape(matrix, g_square);
	matrix.w.x = 5.0f;
	drawShape(matrix, g_lineStrip);
	matrix.w.x = 10.0f;
	drawShape(matrix, g_lines);

	// draw the same shapes again (just below), using sucky immediate mode
	setColour(1.0f, 1.0f, 0.0f);

	// draw a circle
	for(float angle = -PI; angle <= PI; angle += 0.2)
	{
		Vec3 p(cos(angle), sin(angle), -2.0f);
		p += Vec3(-10.0f, -5.0f, 0);
		drawPoint(p);
	}

	// construct a square from a line loop
	{
		Vec3 points[] = 
		{
			Vec3(-6.0f,-4.0f, -2.0f), 
			Vec3(-4.0f,-4.0f, -2.0f), 
			Vec3(-4.0f,-6.0f, -2.0f), 
			Vec3(-6.0f,-6.0f, -2.0f)
		};
		drawLineLoop(points, 4);
	}

	// construct a line strip
	{
		Vec3 points[] = 
		{
			Vec3( 6.0f,-4.0f, -2.0f),
			Vec3( 5.8f,-6.0f, -2.0f),
			Vec3( 4.2f,-6.0f, -2.0f),
			Vec3( 4.0f,-4.0f, -2.0f)
		};
		drawLineStrip(points, 4);
	}

	// construct a little cross
	{
		drawLine(Vec3(11.0f, -5.0f, -2.0f), Vec3(9.0f, -5.0f, -2.0f));
		drawLine(Vec3(10, -6.0f, -2.0f), Vec3(10, -4.0f, -2.0f));
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
