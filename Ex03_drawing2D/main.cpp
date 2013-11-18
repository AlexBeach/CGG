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
			Vec2 p(cos(angle), sin(angle));
			drawPoint(p);
		}
		endShape();
	}

	// construct a square from a line loop
	{
		g_square = beginShape();
		Vec2 points[] = 
		{
			Vec2(-1.0f, 1.0f), 
			Vec2( 1.0f, 1.0f), 
			Vec2( 1.0f,-1.0f), 
			Vec2(-1.0f,-1.0f)
		};
		drawLineLoop(points, 4);
		endShape();
	}

	// construct a line strip
	{
		g_lineStrip = beginShape();
		Vec2 points[] = 
		{
			Vec2(1.0f, 1.0f),
			Vec2(0.8f,-1.0f),
			Vec2(-0.8f,-1.0f),
			Vec2(-1.0f, 1.0f)
		};
		drawLineStrip(points, 4);
		endShape();
	}

	// construct a little cross
	{
		g_lines = beginShape();
		drawLine(Vec2(-1.0f, 0), Vec2(1.0f, 0));
		drawLine(Vec2(0, -1.0f), Vec2(0, 1.0f));
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
}

//------------------------------------------------------------------------------------------------------------------------------------
// called when we want to draw a 2D overlay
//------------------------------------------------------------------------------------------------------------------------------------
void draw()
{
	setColour(1.0f, 1.0f, 1.0f);

	// draw all of the shapes using nice and efficient display lists... :)
	Matrix2 matrix;
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
		Vec2 p(cos(angle), sin(angle));
		p += Vec2(-10.0f, -5.0f);
		drawPoint(p);
	}

	// construct a square from a line loop
	{
		Vec2 points[] = 
		{
			Vec2(-6.0f,-4.0f), 
			Vec2(-4.0f,-4.0f), 
			Vec2(-4.0f,-6.0f), 
			Vec2(-6.0f,-6.0f)
		};
		drawLineLoop(points, 4);
	}

	// construct a line strip
	{
		Vec2 points[] = 
		{
			Vec2( 6.0f,-4.0f),
			Vec2( 5.8f,-6.0f),
			Vec2( 4.2f,-6.0f),
			Vec2( 4.0f,-4.0f)
		};
		drawLineStrip(points, 4);
	}

	// construct a little cross
	{
		drawLine(Vec2(11.0f, -5.0f), Vec2(9.0f, -5.0f));
		drawLine(Vec2(10, -6.0f), Vec2(10, -4.0f));
	}
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
