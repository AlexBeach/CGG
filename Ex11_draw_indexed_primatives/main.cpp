#include "cgg/Graphics.h"
#include <iostream>

// This example uses indexed primitives to draw some geometry (just a cube in this case!). 
// When drawing indexed primitves, we need each of the vertices in it's own array. In this case I'm using just Vec3's, but you can also 
// use the VertexNormal, VertexColour, or VertexNormalColour structs.
// So here we have the 8 vertices that form a cube:
// 
Vec3 g_points[] = 
{
	// +ve Z
	Vec3(-1.0f, -1.0f, 1.0f),
	Vec3( 1.0f, -1.0f, 1.0f),
	Vec3( 1.0f,  1.0f, 1.0f),
	Vec3(-1.0f,  1.0f, 1.0f),

	// -ve Z
	Vec3(-1.0f,  1.0f, -1.0f),
	Vec3( 1.0f,  1.0f, -1.0f),
	Vec3( 1.0f, -1.0f, -1.0f),
	Vec3(-1.0f, -1.0f, -1.0f)
};

// And now we have an array of 24 indices that define each line that makes up the cube
int g_indices[] = 
{
	// +ve Z face
	0, 1,
	1, 2,
	2, 3,
	3, 0,

	// -ve Z face
	4, 5,
	5, 6,
	6, 7,
	7, 4,

	// and the 4 lines to connect both faces
	0, 7,
	1, 6,
	2, 5,
	3, 4
};

//------------------------------------------------------------------------------------------------------------------------------------
// called when we initialise the app
//------------------------------------------------------------------------------------------------------------------------------------
void init()
{
	setWindowTitle("Indexed Primitives");
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

	// draw the cube in white
	setColour(1.0f, 1.0f, 1.0f);

	// Arguments are:
	// The vertex array
	// The index array
	// The number of indices
	// The typ0e of geometry to draw
	drawPrimitives(g_points, g_indices, 24, kLines);
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
void mousePress(int /*button*/, int x, int y)
{
	Vec2 p = getScreenCoordinates(x, y);
}

//------------------------------------------------------------------------------------------------------------------------------------
/// called when the left mouse button is released
//------------------------------------------------------------------------------------------------------------------------------------
void mouseRelease(int /*button*/, int x, int y)
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
