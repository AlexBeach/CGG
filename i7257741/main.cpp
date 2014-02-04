#include "cgg/Graphics.h"
#include <iostream>
#define WIN_32_LEAN_AND_MEAN
#include <windows.h>
#include <GL/GL.h>

float g_time = 0;

Matrix2 GolfCoursePos,GolfCourseExtra1Pos,GolfCourseExtra2Pos,TreePos;
int GolfCourse,GolfCourseExtra1,GolfCourseExtra2,Tree;

//------------------------------------------------------------------------------------------------------------------------------------
// called when we initialise the app
//------------------------------------------------------------------------------------------------------------------------------------
void init()
{
	// give our app a title 
	setWindowTitle("My Amazing Golf Game");

	// sets the size of the 2D screen coordinates. I'm just initialising the defaults here. You can use whatever you want
	// args are: minx, maxx, miny, maxy
	setScreenCoordinates(-20.0f, 20.0f, -16.0f, 16.0f);

	//Setting the background colour to a default grey.
	setBackgroundColour(0.0f,0.75f,0.0f);

	GolfCourse=beginShape();

	Vec2 GolfCoursePoints[] = 
	{
		Vec2 (-2.0f,-1.0f),
		Vec2 (-2.0f,1.0f),
		Vec2 (-5.0f,1.0f),
		Vec2 (-5.0f,4.0f),
		Vec2 (-8.0f,4.0f),		//5
		Vec2 (-8.0f,10.0f),
		Vec2 (-7.0f,10.0f),
		Vec2 (-6.0f,8.0f),
		Vec2 (-4.0f,7.0f),
		Vec2 (-4.0f,5.0f),		//10
		Vec2 (3.0f,5.0f),
		Vec2 (3.0f,4.0f),
		Vec2 (-1.0f,4.0f),
		Vec2 (-1.0f,1.0f),
		Vec2 (1.0f,1.0f),		//15
		Vec2 (1.0f,2.0f),
		Vec2 (9.0f,2.0f),
		Vec2 (9.0f,7.0f),
		Vec2 (5.0f,7.0f),
		Vec2 (5.0f,12.0f),		//20
		Vec2 (1.0f,12.0f),
		Vec2 (0.0f,14.0f),
		Vec2 (-2.0f,15.0f),
		Vec2 (-4.0f,15.0f),
		Vec2 (-6.0f,14.0f),		//25
		Vec2 (-7.0f,12.0f),
		Vec2 (-10.0f,12.0f),
		Vec2 (-10.0f,2.0f),
		Vec2 (-7.0f,2.0f),
		Vec2 (-7.0f,-1.0f),		//30
		Vec2 (-10.0f,-1.0f),
		Vec2 (-10.0f,-12.0f),
		Vec2 (-7.0f,-12.0f),
		Vec2 (-6.0f,-14.0f),
		Vec2 (-4.0f,-15.0f),	//35
		Vec2 (-2.0f,-15.0f),
		Vec2 (0.0f,-14.0f),
		Vec2 (1.0f,-12.0f),
		Vec2 (4.0f,-12.0f),
		Vec2 (4.0f,-14.0f),		//40
		Vec2 (10.0f,-14.0f),
		Vec2 (10.0f,1.0f),
		Vec2 (2.0f,1.0f),
		Vec2 (2.0f,-1.0f),
		Vec2 (8.0f,-1.0f),		//45
		Vec2 (8.0f,-12.0f),
		Vec2 (7.0f,-12.0f),
		Vec2 (7.0f,-10.0f),
		Vec2 (1.0f,-10.0f),
		Vec2 (0.0f,-8.0f),		//50
		Vec2 (-2.0f,-7.0f),
		Vec2 (-2.0f,-6.0f),
		Vec2 (5.0f,-6.0f),
		Vec2 (5.0f,-2.0f),
		Vec2 (1.0f,-2.0f),		//55
		Vec2 (1.0f,-1.0f),
		Vec2 (-1.0f,-1.0f),
		Vec2 (-1.0f,-4.0f),
		Vec2 (3.0f,-4.0f),
		Vec2 (3.0f,-5.0f),		//60
		Vec2 (-4.0f,-5.0f),
		Vec2 (-4.0f,-7.0f),
		Vec2 (-6.0f,-8.0f),
		Vec2 (-7.0f,-10.0f),
		Vec2 (-8.0f,-10.0f),	//65
		Vec2 (-8.0f,-3.0f),		
		Vec2 (-5.0f,-3.0f),
		Vec2 (-5.0f,-1.0f),
		Vec2 (-2.0f,-1.0f),		//69=Fin
	};

	setColour(1.0f,1.0f,1.0f);
	drawLineLoop(GolfCoursePoints,69);

	endShape();

	GolfCoursePos.w.x=0.0f;
	GolfCoursePos.w.y=0.0f;

	GolfCourseExtra1=beginShape();

	Vec2 GolfCourseExtra1PosPoints[] = 
	{
		Vec2 (-2.0f,7.0f),
		Vec2 (0.0f,8.0f),
		Vec2 (1.0f,10.0f),
		Vec2 (3.0f,10.0f),
		Vec2 (3.0f,6.0f),		//5
		Vec2 (-2.0f,6.0f),
		Vec2 (-2.0f,7.0f),		//7=Fin
	};

	setColour(1.0f,1.0f,1.0f);
	drawLineLoop(GolfCourseExtra1PosPoints,7);

	endShape();

	GolfCourseExtra1Pos.w.x=0.0f;
	GolfCourseExtra1Pos.w.y=0.0f;

	GolfCourseExtra2=beginShape();

	Vec2 GolfCourseExtra2PosPoints[] = 
	{
		Vec2 (5.0f,5.0f),
		Vec2 (7.0f,5.0f),
		Vec2 (7.0f,4.0f),
		Vec2 (5.0f,4.0f),
		Vec2 (5.0f,5.0f),		//5 and 5=Fin
	};

	setColour(1.0f,1.0f,1.0f);
	drawLineLoop(GolfCourseExtra2PosPoints,5);

	endShape();

	GolfCourseExtra2Pos.w.x=0.0f;
	GolfCourseExtra2Pos.w.y=0.0f;

//	Tree=beginShape();
//
//	Vec2 TreePosPoints[] = 
//	{
//		Vec2 (0.0f,1.4f),
//		Vec2 (0.4f,1.76f),
//		Vec2 (1.0f,1.6f),
//		Vec2 (1.2f,1.2f),
//		Vec2 (1.2f,0.8f),		//5
//		Vec2 (1.6f,0.6f),
//		Vec2 (1.9f,0.3f),
//		Vec2 (2.0f,-0.1f),
//		Vec2 (1.8f,-0.4f),
//		Vec2 (1.4f,-0.7f),		//10
//		Vec2 (1.4f,-1.2f),
//		Vec2 (1.2f,-1.6f),
//		Vec2 (0.7f,-1.8f),
//		Vec2 (0.1f,-1.5f),
//		Vec2 (-0.4f,-1.7f),		//15
//		Vec2 (-1.0f,-1.5f),
//		Vec2 (-1.2f,-1.2f),
//		Vec2 (-1.18f,-0.8f),
//		Vec2 (-1.6f,-0.8f),
//		Vec2 (-1.84f,-0.4f),	//20
//		Vec2 (-2.0f,0.0f),
//		Vec2 (-1.8f,0.4f),
//		Vec2 (-1.4f,0.6f),
//		Vec2 (-1.46f,1.0f),
//		Vec2 (-1.3f,1.48f),		//25
//		Vec2 (-0.82f,1.76f),
//		Vec2 (-0.36f,1.64f),
//		Vec2 (0.0f,1.4f),		//28=Fin
//	};
//
//	setColour(0.0f,1.0f,0.0f);
//	drawLineLoop(TreePosPoints,5);
//
//	endShape();
//
//	TreePos.w.x=0.0f;
//	TreePos.w.y=0.0f;
//}

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
// Called after draw3D. Allows you to draw a 2D overlay.
//------------------------------------------------------------------------------------------------------------------------------------
void draw()
{
	glLineWidth(4.0);

	drawShape(GolfCoursePos,GolfCourse);
	drawShape(GolfCourseExtra1Pos,GolfCourseExtra1);
	drawShape(GolfCourseExtra2Pos,GolfCourseExtra2);
	drawText(-19.0f, 15.0f, "Score: " );
	drawShape(TreePos,Tree);
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