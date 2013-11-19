#include "cgg/Graphics.h"
#include <iostream>

float g_time = 0;

// these 3 angles are used to control the 3 segments of the arm. 
float g_angle0 = 0;
float g_angle1 = 0;
float g_angle2 = 0;

// vertex normals for a box
VertexNormal g_pointsVN[] = 
{
	// +ve Z
	{ Vec3(-0.3f, -1.0f, 0.3f), Vec3(0.0f, 0.0f, 1.0f) },
	{ Vec3( 0.3f, -1.0f, 0.3f), Vec3(0.0f, 0.0f, 1.0f) },
	{ Vec3( 0.3f,  0.0f, 0.3f), Vec3(0.0f, 0.0f, 1.0f) },
	{ Vec3(-0.3f,  0.0f, 0.3f), Vec3(0.0f, 0.0f, 1.0f) },

	// -ve Z
	{ Vec3(-0.3f,  0.0f, -0.3f), Vec3(0.0f, 0.0f, -1.0f) },
	{ Vec3( 0.3f,  0.0f, -0.3f), Vec3(0.0f, 0.0f, -1.0f) },
	{ Vec3( 0.3f, -1.0f, -0.3f), Vec3(0.0f, 0.0f, -1.0f) },
	{ Vec3(-0.3f, -1.0f, -0.3f), Vec3(0.0f, 0.0f, -1.0f) },

	// +ve Y
	{ Vec3(-0.3f, 0.0f,-0.3f), Vec3(0.0f, 1.0f, 0.0f) },
	{ Vec3(-0.3f, 0.0f, 0.3f), Vec3(0.0f, 1.0f, 0.0f) },
	{ Vec3( 0.3f, 0.0f, 0.3f), Vec3(0.0f, 1.0f, 0.0f) },
	{ Vec3( 0.3f, 0.0f,-0.3f), Vec3(0.0f, 1.0f, 0.0f) },

	// -ve Y
	{ Vec3( 0.3f, -1.0f, -0.3f), Vec3(0.0f, -1.0f, 0.0f) },
	{ Vec3( 0.3f, -1.0f,  0.3f), Vec3(0.0f, -1.0f, 0.0f) },
	{ Vec3(-0.3f, -1.0f,  0.3f), Vec3(0.0f, -1.0f, 0.0f) },
	{ Vec3(-0.3f, -1.0f, -0.3f), Vec3(0.0f, -1.0f, 0.0f) },

	// +ve X
	{ Vec3(0.3f, -1.0f,-0.3f), Vec3(1.0f, 0.0f, 0.0f) },
	{ Vec3(0.3f, -1.0f, 0.3f), Vec3(1.0f, 0.0f, 0.0f) },
	{ Vec3(0.3f,  0.0f, 0.3f), Vec3(1.0f, 0.0f, 0.0f) },
	{ Vec3(0.3f,  0.0f,-0.3f), Vec3(1.0f, 0.0f, 0.0f) },

	// -ve X
	{ Vec3(-0.3f,  0.0f, -0.3f), Vec3(-1.0f, 0.0f, 0.0f) },
	{ Vec3(-0.3f,  0.0f,  0.3f), Vec3(-1.0f, 0.0f, 0.0f) },
	{ Vec3(-0.3f, -1.0f,  0.3f), Vec3(-1.0f, 0.0f, 0.0f) },
	{ Vec3(-0.3f, -1.0f, -0.3f), Vec3(-1.0f, 0.0f, 0.0f) }
};


//------------------------------------------------------------------------------------------------------------------------------------
// called when we initialise the app
//------------------------------------------------------------------------------------------------------------------------------------
void init()
{
	setWindowTitle("Controls: Q/A - Angle0. W/S - Angle 2. E/D - Angle 3.");
}

//------------------------------------------------------------------------------------------------------------------------------------
// called when we need to update the app. 'dt' is the time delta (the number of seconds since the last frame)
//------------------------------------------------------------------------------------------------------------------------------------
void update(float dt)
{
	g_time += dt;

	// modify the angle if any keys are pressed
	float angular_speed = dt * PI;
	if(isKeyPressed('q')) g_angle0 += angular_speed;
	if(isKeyPressed('a')) g_angle0 -= angular_speed;
	if(isKeyPressed('w')) g_angle1 += angular_speed;
	if(isKeyPressed('s')) g_angle1 -= angular_speed;
	if(isKeyPressed('e')) g_angle2 += angular_speed;
	if(isKeyPressed('d')) g_angle2 -= angular_speed;
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

	enableLighting();

	// the axis each segment will rotate around
	Vec3 z_axis(0, 0, 1.0f);

	// push a new matrix onto the stack (for the first segment)
	pushMatrix();
	{
		// rotate by the angle 0
		rotate(g_angle0, z_axis);

		// draw the box
		setColour(1.0f, 0.0f, 0.0f);
		drawPrimitives(g_pointsVN, 24, kQuads);

		// push a new matrix onto the stack (for the second segment)
		pushMatrix();
		{
			// move down a bit (this only affects the 2nd and 3rd segments)
			translate(0, -1.0f, 0);

			// rotate by the second angle
			rotate(g_angle1, z_axis);

			// draw the third box
			setColour(0.0f, 1.0f, 0.0f);
			drawPrimitives(g_pointsVN, 24, kQuads);

			// push a new matrix onto the stack (for the third segment)
			pushMatrix();
			{
				// move down a bit (this only affects the 3rd segments)
				translate(0, -1.0f, 0);

				// rotate by the third angle
				rotate(g_angle2, z_axis); 

				// draw the box
				setColour(0.0f, 0.0f, 1.0f);
				drawPrimitives(g_pointsVN, 24, kQuads);
			}
			popMatrix();
		}
		popMatrix();
	}
	popMatrix();

	disableLighting();
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
