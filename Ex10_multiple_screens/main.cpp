#include "cgg/Graphics.h"
#include <iostream>

float g_timer = 0;

//------------------------------------------------------------------------------------------------------------------------------------
// This example demonstrates a cleanish approach to having multiple screens (e.g. A main menu, instructions, and main game). This isn't
// the only way to do this (a state machine would work just as well, although classes + virtual functions + inheritance would be the
// cleanest option). 
//------------------------------------------------------------------------------------------------------------------------------------

// Declare an update function pointer type. (Takes a float as an argument, returns void, and the function pointer type is called 'UpdateFn')
typedef void (*UpdateFn)(float);

// Declare a draw function pointer type. (Takes no arguments, returns void, and the function pointer type is called 'DrawFn')
typedef void (*DrawFn)();

// the 3 update funcs
void updateScreen1(float dt);
void updateScreen2(float dt);
void updateScreen3(float dt);

// the 3 draw funcs
void drawScreen1();
void drawScreen2();
void drawScreen3();

// A global pointer to the update function for the current screen
UpdateFn g_update = updateScreen1;

// A global pointer to the draw function for the current screen
DrawFn g_draw = drawScreen1;

//------------------------------------------------------------------------------------------------------------------------------------
// The First Screen
//------------------------------------------------------------------------------------------------------------------------------------
void updateScreen1(float dt)
{
	g_timer += dt;

	// if '2' is pressed, change screen... 
	if(isKeyPressed('2') && g_timer > 0.5f)
	{
		g_timer = 0;

		// ... by simply changing the functions pointed to by our global function pointers
		g_update = updateScreen2;
		g_draw = drawScreen2;
	}
}

void drawScreen1()
{
	drawText(5.0f*cos(g_timer), 5.0f*sin(g_timer), "Hello from screen 1!");
}

//------------------------------------------------------------------------------------------------------------------------------------
// The Second Screen
//------------------------------------------------------------------------------------------------------------------------------------
void updateScreen2(float dt)
{
	g_timer += dt;

	// if '3' is pressed, change screen... 
	if(isKeyPressed('3') && g_timer > 0.5f)
	{
		g_timer = 0;

		// ... by simply changing the functions pointed to by our global function pointers
		g_update = updateScreen3;
		g_draw = drawScreen3;
	}

	// if '1' is pressed, change screen... 
	if(isKeyPressed('1') && g_timer > 0.5f)
	{
		g_timer = 0;

		// ... by simply changing the functions pointed to by our global function pointers
		g_update = updateScreen1;
		g_draw = drawScreen1;
	}
}

void drawScreen2()
{
	drawText(0, 6.0f*sin(g_timer), "Hello from screen 2!");
}

//------------------------------------------------------------------------------------------------------------------------------------
// The Third Screen
//------------------------------------------------------------------------------------------------------------------------------------
void updateScreen3(float dt)
{
	g_timer += dt;

	// if '2' is pressed, change screen... 
	if(isKeyPressed('2') && g_timer > 0.5f)
	{
		g_timer = 0;

		// ... by simply changing the functions pointed to by our global function pointers
		g_update = updateScreen2;
		g_draw = drawScreen2;
	}
}

void drawScreen3()
{
	drawText(10.0f*cos(g_timer), 0, "Hello from screen 3!");
}

//------------------------------------------------------------------------------------------------------------------------------------
// called when we initialise the app
//------------------------------------------------------------------------------------------------------------------------------------
void init()
{
	// setting the background colour to a default grey!
	setBackgroundColour(0.6f, 0.6f, 0.7f);
}

//------------------------------------------------------------------------------------------------------------------------------------
// called when we need to update the app. 'dt' is the time delta (the number of seconds since the last frame)
//------------------------------------------------------------------------------------------------------------------------------------
void update(float dt)
{
	// Use our global function pointer to call the correct update function
	g_update(dt);
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
	// Use our global function pointer to call the correct draw function
	g_draw();
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
