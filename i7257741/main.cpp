#include "cgg/Graphics.h"
#include <iostream>
#define WIN_32_LEAN_AND_MEAN
#include <windows.h>
#include <GL/GL.h>

float g_time=0,GolfClubAim=0,BallPower=1;
bool CanMove=true,PowerUp=false,SpaceKeyRelease=false;
Matrix2 GolfCoursePos,GolfCourseExtra1Pos,GolfCourseExtra2Pos,TreePos,HolePos,GolfBallPos,GolfClubofSortsPos;
int GolfCourse,GolfCourseExtra1,GolfCourseExtra2,Tree,Hole,GolfBall,GolfClubofSorts,Score=0,Strokes=0;

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

	setColour(1.0f,1.0f,1.0f);
	drawLineLoop(GolfCoursePoints,69);

	endShape();

	GolfCoursePos.w.x=0.0f;
	GolfCoursePos.w.y=0.0f;

	GolfCourseExtra1=beginShape();

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

	//Tree=beginShape();

	//Vec2 TreePosPoints[] = 
	//{
	//	Vec2 (0.0f,1.4f),
	//	Vec2 (0.4f,1.76f),
	//	Vec2 (1.0f,1.6f),
	//	Vec2 (1.2f,1.2f),
	//	Vec2 (1.2f,0.8f),		//5
	//	Vec2 (1.6f,0.6f),
	//	Vec2 (1.9f,0.3f),
	//	Vec2 (2.0f,-0.1f),
	//	Vec2 (1.8f,-0.4f),
	//	Vec2 (1.4f,-0.7f),		//10
	//	Vec2 (1.4f,-1.2f),
	//	Vec2 (1.2f,-1.6f),
	//	Vec2 (0.7f,-1.8f),
	//	Vec2 (0.1f,-1.5f),
	//	Vec2 (-0.4f,-1.7f),		//15
	//	Vec2 (-1.0f,-1.5f),
	//	Vec2 (-1.2f,-1.2f),
	//	Vec2 (-1.18f,-0.8f),
	//	Vec2 (-1.6f,-0.8f),
	//	Vec2 (-1.84f,-0.4f),	//20
	//	Vec2 (-2.0f,0.0f),
	//	Vec2 (-1.8f,0.4f),
	//	Vec2 (-1.4f,0.6f),
	//	Vec2 (-1.46f,1.0f),
	//	Vec2 (-1.3f,1.48f),		//25
	//	Vec2 (-0.82f,1.76f),
	//	Vec2 (-0.36f,1.64f),
	//	Vec2 (0.0f,1.4f),		//28=Fin
	//};

	//setColour(0.0f,1.0f,0.0f);
	//drawLineLoop(TreePosPoints,28);

	//endShape();

	TreePos.w=(9.0f,9.0f);

	Hole=beginShape();

	for(float angle = -PI; angle <= PI; angle += 0.05)
	{
		Vec2 p(cos(angle)/3, sin(angle)/3);
		setColour(0.0f,0.0f,0.0f);
		drawPoint(p);
	}

	endShape();

	HolePos.w.x=-3.0f;
	HolePos.w.y=-11.0f;

	//For the arrow to show the current angle that the ball's direction will go in
	GolfClubofSorts = beginShape();
		
		Vec2 ClubPoints[] = 
		{
			Vec2(0.0f,0.0f),
			Vec2(0.0f,2.0f),
			Vec2(0.5f,1.5f),
			Vec2(0.0f,2.0f),
			Vec2(-0.5f,1.5f),
			Vec2(0.0f,2.0f),
			Vec2(0.0f,0.0f),
		};

		setColour(1.0f, 0.0f, 0.0f);
		drawLineLoop(ClubPoints, 7);

	endShape();

	GolfClubofSortsPos.w.x=-3.0f;
	GolfClubofSortsPos.w.y=11.0f;

	//For the Golf Ball
	GolfBall=beginShape();

		for(float angle = -PI; angle <= PI; angle += 0.05)
		{
			Vec2 p(cos(angle)/5, sin(angle)/5);
			setColour(1.0f,1.0f,1.0f);
			drawPoint(p);
		}
		setColour(1.0f, 1.0f, 1.0f);

	endShape();

	GolfBallPos.w.x=-3.0f;
	GolfBallPos.w.y=11.0f;
}

//------------------------------------------------------------------------------------------------------------------------------------
// called when we need to update the app. 'dt' is the time delta (the number of seconds since the last frame)
//------------------------------------------------------------------------------------------------------------------------------------
void update(float dt)
{
	g_time+=dt;

	float ca=cos(GolfClubAim);
	float sa=sin(GolfClubAim);
	GolfClubofSortsPos.x.x=ca;
	GolfClubofSortsPos.x.y=sa;
	GolfClubofSortsPos.y.x=-sa;
	GolfClubofSortsPos.y.y=ca;

	float AimSpeed=TWO_PI*dt;

	if(CanMove==true)
	{
		//Rotate ship right
		if(isKeyPressed('d'))
		{
			GolfClubAim-=AimSpeed;
		}

		//Rotate ship left
		if(isKeyPressed('a'))
		{
			GolfClubAim+=AimSpeed;
		}
	}
	else
	{
		if((isKeyPressed(' ')==false)&&(SpaceKeyRelease==false))
		{
			SpaceKeyRelease=true;
		}

		if(SpaceKeyRelease==true)
		{
			GolfBallPos.w=GolfBallPos.w+GolfBallPos.y*(BallPower*dt);
			BallPower-=dt;
		}
		else
		{
			if(BallPower<=20)
			{
				BallPower=BallPower+0.2;
			}
		}

		if(BallPower<=0)
		{
			CanMove=true;
			GolfClubofSortsPos=GolfBallPos;
		}
	}

	if((isKeyPressed(' ')==true)&&(CanMove==true))
	{
		GolfBallPos=GolfClubofSortsPos;
		BallPower=1;
		CanMove=false;
		SpaceKeyRelease=false;
	}

	if(isKeyPressed(kKeyEscape)==true)
	{
		exit(0);
	}
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
	drawShape(TreePos,Tree);
	drawShape(HolePos,Hole);
	if(CanMove==true)
	{
		drawShape(GolfClubofSortsPos,GolfClubofSorts);
	}
	drawShape(GolfBallPos,GolfBall);
	drawText(-19.0f,15.0f,"Score: %i",Score);
	drawText(-19.0f,14.5f,"Strokes: %i",Strokes);
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