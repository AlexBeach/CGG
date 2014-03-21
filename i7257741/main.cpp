#include "cgg/Graphics.h"
#include <iostream>
#define WIN_32_LEAN_AND_MEAN
#include <windows.h>
#include <GL/GL.h>
#include <time.h>

float g_time=0,GolfClubAim=0,BallPower=1;
bool CanMove=true,PowerUp=false,SpaceKeyRelease=false,Win=false,Portal=false,Help=false,
Cheat=false;
Matrix2 GolfCoursePos,GolfCourseExtra1Pos,GolfCourseExtra2Pos,TreePos,HoleWinPos,
GolfBallPos,GolfClubofSortsPos,HolePortal1Pos,HolePortal2Pos,HolePortal3Pos,HolePortal4Pos,
PowerBarOuterPos,PowerBarInner1Pos,PowerBarInner2Pos,PowerBarInner3Pos,PowerBarInner4Pos,
PowerBarInner5Pos,HoleWinCollisionPos,HoleCollision1Pos,HoleCollision2Pos,HoleCollision3Pos,
HoleCollision4Pos;
int GolfCourse,GolfCourseExtra1,GolfCourseExtra2,Tree,HoleWin,GolfBall,GolfClubofSorts,
Score=0,Strokes=0,Par=5,HolePortal1,HolePortal2,HolePortal3,HolePortal4,PowerBarOuter,
PowerBarInner1,PowerBarInner2,PowerBarInner3,PowerBarInner4,PowerBarInner5,HoleWinCollision,
HoleCollision1,HoleCollision2,HoleCollision3,HoleCollision4,PortalNum=0;

float FindIntersect(Vec2 P,Vec2 D,Vec2 A,Vec2 B)										//Find intersect function is entered every time to check if there has been an intersection between the ball and the line between two points for any particulatar vector.
{
	//Converts into a vector quantity
 	Vec2 BA=B-A;

	//Checks determinant to make sure there is an intersection
 	float Determinant=BA.x*D.y-BA.y*D.x;
 	if(fabs(Determinant)>0.00001f)
 	{
		//Computes the distance along 'D' where the intersection occurs.
 		float DistanceD=(BA.y*(P.x-A.x)-BA.x*(P.y-A.y))/Determinant;

		//Computes the distance along the line a->b where the intersection occurs.
 		float G;

		// avoid division by zero!
 		if(fabs(BA.x)>0.00001f)
 		{
 			G=(P.x+(D.x*DistanceD)-A.x)/BA.x;
 		}
 		else
 		{
 			G=(P.y+(D.y*DistanceD)-A.y)/BA.y;
 		}

		//Collision occured if 'G' is between 0 and 1.
 		if((G>=0)&&(G<=1.0f))
 		{
 			return DistanceD;
 		}
	}
	else
	{
		//No intersection found
 		return -1;
	}
 }

Vec2 GolfCoursePoints[]=				//points for the main part of the gold course
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

Vec2 GolfCourseExtra1Points[]=			//points for another part for the golf course
{
	Vec2 (-2.0f,7.0f),
	Vec2 (0.0f,8.0f),
	Vec2 (1.0f,10.0f),
	Vec2 (3.0f,10.0f),
	Vec2 (3.0f,6.0f),		//5
	Vec2 (-2.0f,6.0f),
	Vec2 (-2.0f,7.0f),		//7=Fin
};

Vec2 GolfCourseExtra2Points[]=			//points for the final part fo the golf course
{
	Vec2 (5.0f,5.0f),
	Vec2 (7.0f,5.0f),
	Vec2 (7.0f,4.0f),
	Vec2 (5.0f,4.0f),
	Vec2 (5.0f,5.0f),	//5 and 5=Fin
};

Vec2 HoleWinCollisionPoints[]=				//points for the hidden square that acts are the hole's collision
{
	Vec2 (-3.2f,-11.2f),
	Vec2 (-2.8f,-11.2f),
	Vec2 (-2.8f,-10.8f),
	Vec2 (-3.2f,-10.8f),
	Vec2 (-3.2f,-11.2f),	//5 and 5=Fin
};

Vec2 HoleCollision1Points[]=				//points for more hole collision
{
	Vec2 (0.2f,1.75f),
	Vec2 (-0.2f,1.75f),
	Vec2 (-0.2f,1.35f),
	Vec2 (0.2f,1.35f),
	Vec2 (0.2f,1.75f),	//5 and 5=Fin
};

Vec2 HoleCollision2Points[]=				//points for more hole collision
{
	Vec2 (2.8f,0.2f),
	Vec2 (2.4f,0.2f),
	Vec2 (2.4f,-0.2f),
	Vec2 (2.8f,-0.2f),
	Vec2 (2.8f,0.2f),	//5 and 5=Fin
};

Vec2 HoleCollision3Points[]=				//points for more hole collision
{
	Vec2 (0.2f,-1.75f),
	Vec2 (-0.2f,-1.75f),
	Vec2 (-0.2f,-1.35f),
	Vec2 (0.2f,-1.35f),
	Vec2 (0.2f,-1.75f),	//5 and 5=Fin
};

Vec2 HoleCollision4Points[]=				//points for more hole collision
{
	Vec2 (-2.8f,0.2f),
	Vec2 (-2.4f,0.2f),
	Vec2 (-2.4f,-0.2f),
	Vec2 (-2.8f,-0.2f),
	Vec2 (-2.8f,0.2f),	//5 and 5=Fin
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
	/*setScreenCoordinates(-32.0f, 32.0f, -18.0f, 18.0f);*/

	//Setting the background colour to a default grey.
	setBackgroundColour(0.0f,0.75f,0.0f);

	/*fullScreen(true);*/

	GolfCourse=beginShape();

		setColour(1.0f,1.0f,1.0f);
		drawLineLoop(GolfCoursePoints,69);

	endShape();

	GolfCoursePos.w.x=0.0f;
	GolfCoursePos.w.y=0.0f;

	GolfCourseExtra1=beginShape();

		setColour(1.0f,1.0f,1.0f);
		drawLineLoop(GolfCourseExtra1Points,7);

	endShape();

	GolfCourseExtra1Pos.w.x=0.0f;
	GolfCourseExtra1Pos.w.y=0.0f;

	GolfCourseExtra2=beginShape();

		setColour(1.0f,1.0f,1.0f);
		drawLineLoop(GolfCourseExtra2Points,5);

	endShape();

	GolfCourseExtra2Pos.w.x=0.0f;
	GolfCourseExtra2Pos.w.y=0.0f;

	HoleWin=beginShape();

		for(float Angle=-PI;Angle<=PI;Angle+=0.05)
		{
			Vec2 p(cos(Angle)/3,sin(Angle)/3);
			setColour(0.0f,0.0f,0.0f);
			drawPoint(p);
		}

	endShape();

	HoleWinPos.w.x=-3.0f;
	HoleWinPos.w.y=-11.0f;

	HoleWinCollision=beginShape();

		setColour(0.0f,0.75f,0.0f);
		drawLineLoop(HoleWinCollisionPoints,5);

	endShape();

	HoleWinCollisionPos.w.x=0.0f;
	HoleWinCollisionPos.w.y=0.0f;

	HolePortal1=beginShape();

		for(float Angle=-PI;Angle<=PI;Angle+=0.05)
		{
			Vec2 p(cos(Angle)/3,sin(Angle)/3);
			setColour(1.0f,0.0f,1.0f);
			drawPoint(p);
		}

	endShape();

	HolePortal1Pos.w.x=0.0f;
	HolePortal1Pos.w.y=1.55f;

	HoleCollision1=beginShape();

		setColour(0.0f,0.75f,0.0f);
		drawLineLoop(HoleCollision1Points,5);

	endShape();

	HoleCollision1Pos.w.x=0.0f;
	HoleCollision1Pos.w.y=0.0f;

	HolePortal2=beginShape();

		for(float Angle=-PI;Angle<=PI;Angle+=0.05)
		{
			Vec2 p(cos(Angle)/3, sin(Angle)/3);
			setColour(1.0f,0.0f,1.0f);
			drawPoint(p);
		}

	endShape();

	HolePortal2Pos.w.x=2.6f;
	HolePortal2Pos.w.y=0.0f;

	HoleCollision2=beginShape();

		setColour(0.0f,0.75f,0.0f);
		drawLineLoop(HoleCollision2Points,5);

	endShape();

	HoleCollision2Pos.w.x=0.0f;
	HoleCollision2Pos.w.y=0.0f;

	HolePortal3=beginShape();

		for(float Angle=-PI;Angle<=PI;Angle+=0.05)
		{
			Vec2 p(cos(Angle)/3,sin(Angle)/3);
			setColour(1.0f,0.0f,1.0f);
			drawPoint(p);
		}

	endShape();

	HolePortal3Pos.w.x=0.0f;
	HolePortal3Pos.w.y=-1.55f;

	HoleCollision3=beginShape();

		setColour(0.0f,0.75f,0.0f);
		drawLineLoop(HoleCollision3Points,5);

	endShape();

	HoleCollision3Pos.w.x=0.0f;
	HoleCollision3Pos.w.y=0.0f;


	HolePortal4=beginShape();

		for(float Angle=-PI;Angle<=PI;Angle+=0.05)
		{
			Vec2 p(cos(Angle)/3,sin(Angle)/3);
			setColour(1.0f,0.0f,1.0f);
			drawPoint(p);
		}

	endShape();

	HolePortal4Pos.w.x=-2.6f;
	HolePortal4Pos.w.y=0.0f;

	HoleCollision4=beginShape();

		setColour(0.0f,0.75f,0.0f);
		drawLineLoop(HoleCollision4Points,5);

	endShape();

	HoleCollision4Pos.w.x=0.0f;
	HoleCollision4Pos.w.y=0.0f;

	//For the arrow to show the current Angle that the ball's direction will go in
	GolfClubofSorts = beginShape();
		
		Vec2 ClubPoints[] = 
		{
			Vec2(0.0f,0.0f),
			Vec2(0.0f,2.0f),
			Vec2(0.5f,1.5f),
			Vec2(0.0f,2.0f),
			Vec2(-0.5f,1.5f),	//5
			Vec2(0.0f,2.0f),		
			Vec2(0.0f,0.0f),	//7=Fin
		};

		setColour(1.0f, 0.0f, 0.0f);
		drawLineLoop(ClubPoints, 7);

	endShape();

	GolfClubofSortsPos.w.x=-3.0f;
	GolfClubofSortsPos.w.y=11.0f;

	//For the Golf Ball
	GolfBall=beginShape();

		for(float Angle=-PI;Angle<=PI;Angle+=0.05)
		{
			Vec2 p(cos(Angle)/8,sin(Angle)/8);
			setColour(1.0f,1.0f,1.0f);
			drawPoint(p);
		}
		setColour(1.0f, 1.0f, 1.0f);

	endShape();

	GolfBallPos.w.x=-3.0f;
	GolfBallPos.w.y=11.0f;

	PowerBarOuter=beginShape();

		Vec2 PowerBarOuterPoints[] = 
		{
			Vec2(0.0f,0.0f),
			Vec2(2.6f,0.0f),
			Vec2(2.6f,-0.5f),
			Vec2(0.0f,-0.5f),
			Vec2(0.0f,0.0f),
		};

		setColour(0.0f,0.0f,0.0f);
		drawLineLoop(PowerBarOuterPoints,5);

	endShape();

	PowerBarOuterPos.w.x=-3.0f;
	PowerBarOuterPos.w.y=11.0f;

	PowerBarInner1=beginShape();

		Vec2 PowerBarInner1Points[] = 
		{
			Vec2(0.1f,-0.1f),
			Vec2(0.5f,-0.1f),
			Vec2(0.5f,-0.4f),
			Vec2(0.1f,-0.4f),
			Vec2(0.1f,-0.1f),
		};

		drawLineLoop(PowerBarInner1Points, 5);

	endShape();

	PowerBarInner1Pos.w.x=-3.0f;
	PowerBarInner1Pos.w.y=11.0f;

	PowerBarInner2=beginShape();

		Vec2 PowerBarInner2Points[] = 
		{
			Vec2(0.6f,-0.1f),
			Vec2(1.0f,-0.1f),
			Vec2(1.0f,-0.4f),
			Vec2(0.6f,-0.4f),
			Vec2(0.6f,-0.1f),
		};

		drawLineLoop(PowerBarInner2Points, 5);

	endShape();

	PowerBarInner2Pos.w.x=-3.0f;
	PowerBarInner2Pos.w.y=11.0f;

	PowerBarInner3=beginShape();

		Vec2 PowerBarInner3Points[] = 
		{
			Vec2(1.1f,-0.1f),
			Vec2(1.5f,-0.1f),
			Vec2(1.5f,-0.4f),
			Vec2(1.1f,-0.4f),
			Vec2(1.1f,-0.1f),
		};

		drawLineLoop(PowerBarInner3Points, 5);

	endShape();

	PowerBarInner3Pos.w.x=-3.0f;
	PowerBarInner3Pos.w.y=11.0f;

	PowerBarInner4=beginShape();

		Vec2 PowerBarInner4Points[] = 
		{
			Vec2(1.6f,-0.1f),
			Vec2(2.0f,-0.1f),
			Vec2(2.0f,-0.4f),
			Vec2(1.6f,-0.4f),
			Vec2(1.6f,-0.1f),
		};

		drawLineLoop(PowerBarInner4Points, 5);

	endShape();

	PowerBarInner4Pos.w.x=-3.0f;
	PowerBarInner4Pos.w.y=11.0f;

	PowerBarInner5=beginShape();

		Vec2 PowerBarInner5Points[] = 
		{
			Vec2(2.1f,-0.1f),
			Vec2(2.5f,-0.1f),
			Vec2(2.5f,-0.4f),
			Vec2(2.1f,-0.4f),
			Vec2(2.1f,-0.1f),
		};

		drawLineLoop(PowerBarInner5Points, 5);

	endShape();

	PowerBarInner5Pos.w.x=-3.0f;
	PowerBarInner5Pos.w.y=11.0f;
}

//------------------------------------------------------------------------------------------------------------------------------------
// called when we need to update the app. 'dt' is the time delta (the number of seconds since the last frame)
//------------------------------------------------------------------------------------------------------------------------------------
void update(float dt)
{
	g_time+=dt;

	float ca=cos(GolfClubAim);						//creates and initialises ca and sa, which give the golf club's aim a value using sine and cosine and allows the aim to rotate around
	float sa=sin(GolfClubAim);
	GolfClubofSortsPos.x.x=ca;
	GolfClubofSortsPos.x.y=sa;
	GolfClubofSortsPos.y.x=-sa;
	GolfClubofSortsPos.y.y=ca;

	float AimSpeed=TWO_PI*dt;		//gives aimspeed the value of two PI times dt, which is amount of time between frames (i think)

	if((CanMove==true)&&(Win==false)&&(Help==false))			//if statement entered is the user hasn't won, isn't in the help menu, the ball isn't currently moving and the user isn't holding the space key at the moment.
	{
		//Rotate ship right
		if(isKeyPressed('d')||(isKeyPressed('D')))				//if the user presses and holds d'' they will trun anti-clockwise. press and hold a'' the user will turn clockwise.
		{
			GolfClubAim-=(AimSpeed/3.5);
		}

		//Rotate ship left
		if(isKeyPressed('a')||(isKeyPressed('A')))
		{
			GolfClubAim+=(AimSpeed/3.5);
		}
	}
	else						//if canmove is false then it'll enter the else section. within this part, the movement is done. once the user has released the space key, it sets the space key bool to true so they cannot keep spamming space to ruin the next few if statements
	{
		if((isKeyPressed(' ')==false)&&(SpaceKeyRelease==false)&&(Win==false)&&(Help==false))		
		{
			SpaceKeyRelease=true;
			Portal=false;
			Strokes++;
		}

		if((SpaceKeyRelease==true)&&(Win==false)&&(Help==false))			//once the user has let go of space and the SpaceKeyRelease has been set to true (meaning that they have let go of space and the bool has been changed in the if statement above)
		{
			GolfBallPos.w=GolfBallPos.w+GolfBallPos.y*(BallPower*dt);			//sets movement for the golf ball
			PowerBarOuterPos.w=GolfBallPos.w+GolfBallPos.y*(BallPower*dt);		//moves the hidden (will be unhidden when the ball has stopped and the user is holding space) power bar boxes in the same way as the ball
			PowerBarInner1Pos.w=GolfBallPos.w+GolfBallPos.y*(BallPower*dt);
			PowerBarInner2Pos.w=GolfBallPos.w+GolfBallPos.y*(BallPower*dt);
			PowerBarInner3Pos.w=GolfBallPos.w+GolfBallPos.y*(BallPower*dt);
			PowerBarInner4Pos.w=GolfBallPos.w+GolfBallPos.y*(BallPower*dt);
			PowerBarInner5Pos.w=GolfBallPos.w+GolfBallPos.y*(BallPower*dt);
			BallPower-=2*dt;													//using dt ballpower will slowdown based on the maount time it has been moving.
		}
		else
		{
			if((BallPower<=20)&&(Win==false)&&(Help==false))					//if the user hasn't let go of space, then the ballpower will increase up until it hits, when the ball power is at its maximun.
			{
				BallPower=BallPower+0.2;
			}
		}

		if((BallPower<=0)&&(Win==false)&&(Help==false))							//after the user has let go of space and the ball has moved to where it was aimed at in the amount that the ball power was set to and ball has slowed down to the point that the power has hit 0, this if statement will be entered
		{
			CanMove=true;														//can move is set back to true, meaning that the user can start to aim again and the is space key pressed if statement below
			GolfClubofSortsPos=GolfBallPos;										//the direction arrow is set to the position of the ball so the user can it to help them aim
		}
		
	}

	if((isKeyPressed(' ')==true)&&(CanMove==true)&&(Win==false)&&(Help==false))			//enters the if statement if the user has pressed space, isn't in the help menu and hasn't already won the game.
	{
		GolfBallPos=GolfClubofSortsPos;				//the gold ball is set to the position of the direction arrow
		BallPower=1;								//ballpower is set to 1
		CanMove=false;								//canmove is set to false so that the gold ball can move and the user cannot alter the direction anymore, until the ball has finished moving
		SpaceKeyRelease=false;						//spacekeyrelease is set to false, so that the user has to release the space key again at some point in order to make the ball ove and slow down properly in the above if statements
	}

	float Closest1=10000.0f;				//creates a new float, which is used for the next loop

	Vec2 N1;								//creates a new vec that will also be used in the next loop, which will be for intersection for collision
	
	for(int i=1;i<sizeof(GolfCoursePoints)/sizeof(Vec2);i++)		//for loop start with i=1 and ends when 'i' gets to the same number as the amount of points in golfcoursepoints
	{
		// These are the same two coordinates used to draw the line. 
		float Isect=FindIntersect(GolfBallPos.w,GolfBallPos.y,GolfCoursePoints[i-1],GolfCoursePoints[i]);		//enters find intersect, with the position of the golf ball, the y-position of the golf ball (which is the golf ball's ball direction), a point from the goldcoursepoints and the previous point from golfcoursepoints.

		// if intersection found (e.g. distance returned is not negative)
		if(Isect>=0)
		{
			if(Isect<Closest1)
			{
				Closest1=Isect;
				Vec2 AB(GolfCoursePoints[i-1]-GolfCoursePoints[i]);		//creates vec with two consecutive points from golfcoursepoints
				AB=normalize(AB);			//normalises the recently created vec
				N1.x=-AB.y;					//sets the x coordinate of a vec to the -ve value of the y-coordinate of the recently created and normalised vec
				N1.y=AB.x;					//sets the y coordinate of a vec to the  +ve value of the x-coordinate of the recently created and normalised vec
			}
		}
	}

	float Closest2=10000.0f;

	Vec2 N2;

	for(int i=1;i<sizeof(GolfCourseExtra1Points)/sizeof(Vec2);i++)
	{
		// These are the same two coordinates used to draw the line. 
		float Isect=FindIntersect(GolfBallPos.w,GolfBallPos.y,GolfCourseExtra1Points[i-1],GolfCourseExtra1Points[i]);			//the same equations as above but with the other points needed to fully create everything for the golf course

		// if intersection found (e.g. distance returned is not negative)
		if(Isect>=0)
		{
			if(Isect<Closest2)
			{
				Closest2=Isect;
				Vec2 AB(GolfCourseExtra1Points[i-1]-GolfCourseExtra1Points[i]);
				AB=normalize(AB);
				N2.x=-AB.y;
				N2.y=AB.x;
			}
		}
	}

	float Closest3=10000.0f;

	Vec2 N3;

	for(int i=1;i<sizeof(GolfCourseExtra2Points)/sizeof(Vec2);i++)			//likewise as the few equations above, but with different points, which are needed to fully create everything for the golfcourse.
	{
		// These are the same two coordinates used to draw the line. 
		float Isect=FindIntersect(GolfBallPos.w,GolfBallPos.y,GolfCourseExtra2Points[i-1],GolfCourseExtra2Points[i]);

		// if intersection found (e.g. distance returned is not negative)
		if(Isect>=0)
		{
			if(Isect<Closest3)
			{
				Closest3=Isect;
				Vec2 AB(GolfCourseExtra2Points[i-1]-GolfCourseExtra2Points[i]);
				AB=normalize(AB);
				N3.x=-AB.y;
				N3.y=AB.x;
			}
		}
	}

	if(Closest1<(BallPower*dt))							//if closest, which is either a large value (if there isn't an interaction) or the value of isect from the find intersection function.
	{
		GolfBallPos.y-=2*dot(N1,GolfBallPos.y)*N1;		//changes various coordinates and directions in order to make the ball look as if it has hit the wall and bounced of it.
		GolfBallPos.x.x=GolfBallPos.y.y;				//^^^
		GolfBallPos.x.y=-GolfBallPos.y.x;				//^^^
		BallPower=BallPower-0.2;						//ballpower is made smaller to make it see like hitting the ball slowed it down
		Portal=false;
	}

	if(Closest2<(BallPower*dt))
	{
		GolfBallPos.y-=2*dot(N2,GolfBallPos.y)*N2;
		GolfBallPos.x.x=GolfBallPos.y.y;
		GolfBallPos.x.y=-GolfBallPos.y.x;
		BallPower=BallPower-0.2;
		Portal=false;
	}

	if(Closest3<(BallPower*dt))
	{
		GolfBallPos.y-=2*dot(N3,GolfBallPos.y)*N3;
		GolfBallPos.x.x=GolfBallPos.y.y;
		GolfBallPos.x.y=-GolfBallPos.y.x;
		BallPower=BallPower-0.2;
		Portal=false;
	}

	float Closest4=10000.0f;

	for(int i=1;i<sizeof(HoleWinCollisionPoints)/sizeof(Vec2);i++)
	{
		// These are the same two coordinates used to draw the line. 
		float Isect=FindIntersect(GolfBallPos.w,GolfBallPos.y,HoleWinCollisionPoints[i-1],HoleWinCollisionPoints[i]);

		// if intersection found (e.g. distance returned is not negative)
		if(Isect>=0)
		{
			if(Isect<Closest4)
			{
				Closest4=Isect;						//set the value of isect to the value of closest if the if statement is entered and the if statement is only entered is find interest returns a value that is more 0 and it only does this if there is an interesection
			}
		}
	}

	if(Closest4<(BallPower*dt))
	{
		BallPower=0;					//this if statement is entered if there is a intersection for the ball and the final ball
		GolfBallPos=HoleWinPos;			//sets the postion of the ball to the position of the final hole
		Win=true;						//the intersection means the user has won and won is thus set to true
		Score=Strokes-Par;				//the score is then set. The user's score is the amount of strokes they needed to put the ball minus par.
	}

	float Closest5=10000.0f;

	for(int i=1;i<sizeof(HoleCollision1Points)/sizeof(Vec2);i++)
	{
		// These are the same two coordinates used to draw the line. 
		float Isect=FindIntersect(GolfBallPos.w,GolfBallPos.y,HoleCollision1Points[i-1],HoleCollision1Points[i]);

		// if intersection found (e.g. distance returned is not negative)
		if(Isect>=0)
		{
			if(Isect<Closest5)
			{
				Closest5=Isect;
			}
		}
	}

	if((Closest5<(BallPower*dt))&&(Portal==false))
	{
		Portal=true;											//sets Portal to true

		srand(time(NULL));
		PortalNum=((rand()%20));

		switch(PortalNum)										//switchs statement for PortalNum after it has been given a random number between 0 and 20 by using srand. the switch statement then selects a case based on the number and assigns the position of one of the portals to the golfball based on what case is chosen.
		{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4: GolfBallPos=HolePortal1Pos;
					break;
			case 5:
			case 6:
			case 7:	
			case 8:
			case 9:	GolfBallPos=HolePortal2Pos;
					break;
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:GolfBallPos=HolePortal3Pos;
					break;
			case 15:
			case 16:
			case 17:
			case 18:
			case 19:GolfBallPos=HolePortal4Pos;
					break;
		}
	}

	float Closest6=10000.0f;

	for(int i=1;i<sizeof(HoleCollision2Points)/sizeof(Vec2);i++)
	{
		// These are the same two coordinates used to draw the line. 
		float Isect=FindIntersect(GolfBallPos.w,GolfBallPos.y,HoleCollision2Points[i-1],HoleCollision2Points[i]);

		// if intersection found (e.g. distance returned is not negative)
		if(Isect>=0)
		{
			if(Isect<Closest6)
			{
				Closest6=Isect;
			}
		}
	}

	if((Closest6<(BallPower*dt))&&(Portal==false))
	{
		Portal=true;

		srand(time(NULL));
		PortalNum=((rand()%20));

		switch(PortalNum)
		{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4: GolfBallPos=HolePortal1Pos;
					break;
			case 5:
			case 6:
			case 7:	
			case 8:
			case 9:	GolfBallPos=HolePortal2Pos;
					break;
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:GolfBallPos=HolePortal3Pos;
					break;
			case 15:
			case 16:
			case 17:
			case 18:
			case 19:GolfBallPos=HolePortal4Pos;
					break;
		}
	}

	float Closest7=10000.0f;

	for(int i=1;i<sizeof(HoleCollision3Points)/sizeof(Vec2);i++)
	{
		// These are the same two coordinates used to draw the line. 
		float Isect=FindIntersect(GolfBallPos.w,GolfBallPos.y,HoleCollision3Points[i-1],HoleCollision3Points[i]);

		// if intersection found (e.g. distance returned is not negative)
		if(Isect>=0)
		{
			if(Isect<Closest7)
			{
				Closest7=Isect;
			}
		}
	}

	if((Closest7<(BallPower*dt))&&(Portal==false))
	{
		Portal=true;

		srand(time(NULL));
		PortalNum=((rand()%20));

		switch(PortalNum)
		{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4: GolfBallPos=HolePortal1Pos;
					break;
			case 5:
			case 6:
			case 7:	
			case 8:
			case 9:	GolfBallPos=HolePortal2Pos;
					break;
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:GolfBallPos=HolePortal3Pos;
					break;
			case 15:
			case 16:
			case 17:
			case 18:
			case 19:GolfBallPos=HolePortal4Pos;
					break;
		}
	}

	float Closest8=10000.0f;

	for(int i=1;i<sizeof(HoleCollision4Points)/sizeof(Vec2);i++)
	{
		// These are the same two coordinates used to draw the line. 
		float Isect=FindIntersect(GolfBallPos.w,GolfBallPos.y,HoleCollision4Points[i-1],HoleCollision4Points[i]);

		// if intersection found (e.g. distance returned is not negative)
		if(Isect>=0)
		{
			if(Isect<Closest8)
			{
				Closest8=Isect;
			}
		}
	}

	if((Closest8<(BallPower*dt))&&(Portal==false))
	{
		Portal=true;

		srand(time(NULL));
		PortalNum=((rand()%20));

		switch(PortalNum)
		{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4: GolfBallPos=HolePortal1Pos;
					break;
			case 5:
			case 6:
			case 7:	
			case 8:
			case 9:	GolfBallPos=HolePortal2Pos;
					break;
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:GolfBallPos=HolePortal3Pos;
					break;
			case 15:
			case 16:
			case 17:
			case 18:
			case 19:GolfBallPos=HolePortal4Pos;
					break;
		}
	}

	if((isKeyPressed('r'))||(isKeyPressed('R')))								//enters  if statement the user has pressed 'r'. if the user has pressed 'r' several variables are reset back to their original value and several vecs are set back to original position to make it seem as if the game has started again
	{
		Win=false;
		CanMove=true;
		Help=false;
		SpaceKeyRelease=false;
		Portal=false;
		Score=0;
		Strokes=0;
		GolfBallPos.w.x=-3.0f;
		GolfBallPos.w.y=11.0f;
		BallPower=0;
		GolfClubAim=0;
		GolfClubofSortsPos.w.x=-3.0f;
		GolfClubofSortsPos.w.y=11.0f;
		PowerBarOuterPos.w=GolfBallPos.w+GolfBallPos.y*(BallPower*dt);
		PowerBarInner1Pos.w=GolfBallPos.w+GolfBallPos.y*(BallPower*dt);
		PowerBarInner2Pos.w=GolfBallPos.w+GolfBallPos.y*(BallPower*dt);
		PowerBarInner3Pos.w=GolfBallPos.w+GolfBallPos.y*(BallPower*dt);
		PowerBarInner4Pos.w=GolfBallPos.w+GolfBallPos.y*(BallPower*dt);
		PowerBarInner5Pos.w=GolfBallPos.w+GolfBallPos.y*(BallPower*dt);
	}

	if(isKeyPressed(kKeyF1)==true)							//if the user has pressed F1 Help is set true, which allows the user to enter the if statement for the Help menu, which draws all the text for the help menu and stops the porgram drawing the course and balla nd everything else while in the hlp menu.
	{
		Help=true;
	}

	if((Help==true)&&(isKeyPressed(kKeyBackSpace)))		//if the user is in the help menu and they press the backspace key, help is set to false, which allows them to exit the ehlp menu and then the program will draw abck everything that was there before they entered the help menu, which makes it look as if the help menu was just open on top of the game.
	{
		Help=false;
	}
	
	if(isKeyPressed(kKeyEscape)==true)					//if the user presses the espace key (Esc) the it will enter this if statement, which will go in the exit functiona the game.
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

	if(Help==false)		//Things within this if statement will only show when the help menu is not open.
	{
		drawShape(GolfCoursePos,GolfCourse);				//draws most of the golf course
		drawShape(GolfCourseExtra1Pos,GolfCourseExtra1);	//draws anopther part of the golf course
		drawShape(GolfCourseExtra2Pos,GolfCourseExtra2);	//and draws the last part of the gold course
		drawShape(HoleWinPos,HoleWin);						//draws the final hole
		drawShape(HoleWinCollisionPos,HoleWinCollision);drawShape(HolePortal1Pos,HolePortal1); //draw the hidden collision for final hole
		drawShape(HoleCollision1Pos,HoleCollision1);		//draws the...
		drawShape(HolePortal2Pos,HolePortal2);				//portal holes...
		drawShape(HoleCollision2Pos,HoleCollision2);		//and the ...
		drawShape(HolePortal3Pos,HolePortal3);				//collision needed ...
		drawShape(HoleCollision3Pos,HoleCollision3);		//for them to...
		drawShape(HolePortal4Pos,HolePortal4);				//work and...
		drawShape(HoleCollision4Pos,HoleCollision4);		//collide properly...

		setColour(1.0f,1.0f,1.0f);
		drawText(16.6,15.2,"Hit F1 for help.");				//draws text, telling user how to access the help menu, in the white.
	}

	if((CanMove==true)&&(Help==false))						//if the ball is still, the user isn't holding the space key and the user isn't in the help menu then the direction arrow will be drawn and shown on screen in the same place as the ball
	{
		glLineWidth(2.0);
		setColour(0.0f, 1.0f, 0.0f);
		drawShape(GolfClubofSortsPos,GolfClubofSorts);
	}

	if((isKeyPressed(' ')==true)&&(SpaceKeyRelease==false)&&(Help==false))		//if the user is holding space and isn't in the help menu, then the power bar will be drawn and shown.
	{																			//a square of a different colour, ranging from green to red, is drawn depending on how long the user has held space
		glLineWidth(2.0);
		drawShape(PowerBarOuterPos,PowerBarOuter);

		if(BallPower>=1)
		{
			setColour(0.0f, 1.0f, 0.0f);
			drawShape(PowerBarInner1Pos,PowerBarInner1);
		}

		if(BallPower>=5)
		{
			setColour(0.5f, 1.0f, 0.0f);
			drawShape(PowerBarInner2Pos,PowerBarInner2);
		}

		if(BallPower>=10)
		{
			setColour(1.0f, 1.0f, 0.0f);
			drawShape(PowerBarInner3Pos,PowerBarInner3);
		}

		if(BallPower>=15)
		{
			setColour(1.0f, 0.5f, 0.0f);
			drawShape(PowerBarInner4Pos,PowerBarInner4);
		}

		if(BallPower>=20)
		{
			setColour(1.0f, 0.0f, 0.0f);
			drawShape(PowerBarInner5Pos,PowerBarInner5);
		}
	}

	if(Help==false)													//draws the ball on screen and the score, strokes and par in the top corner if the user isn't in the help menu.
	{
		drawShape(GolfBallPos,GolfBall);
		drawText(-19.5f,15.2f,"Score: %i",Score);
		drawText(-19.5f,14.7f,"Strokes: %i",Strokes);
		drawText(-19.5f,14.2f,"Par=%i",Par);
	}
	
	if(Help==true)																										//if the user has pressed F1 to enter the help menu and hasn't pressed the BackSpace key yet then the help menu will be the only thing shown on screen. the help mneu has help for controls, instructions and the scoring system.
	{
		setColour(1.0f, 1.0f, 1.0f);
		drawText(-7.5f,13.6f,"CONTROLS");
		drawText(-7.5f,13.5f,"_________");
		drawText(-8.0f,12.7f,"- Press and hold the 'A' key to turn anti-clockwise");
		drawText(-8.0f,11.9f,"- Press and hold the 'D' key to turn clockwise");
		drawText(-8.0f,11.1f,"- Press and hold the Space key to increase the power");
		drawText(-8.0f,10.3f,"- Release the Space key to hit the golf ball");
		drawText(-8.0f,9.5f,"- Press the Escape (Esc) key to exit the game.");
		drawText(-8.0f,8.7f,"- Press the 'R' key to restart the game.");
		drawText(-8.0f,7.9f,"- Press the BackSpace key to exit the help page and return to the game.");
		drawText(-7.5f,6.1f,"INSTRUCTIONS");
		drawText(-7.5f,6.0f,"_____________");
		drawText(-8.0f,5.2f,"- The aim of the game is to get your ball into the final hole (the black one)");
		drawText(-8.0f,4.4f,"  in as few strokes as possible (Therefore, the lower your score, the better).");
		drawText(-8.0f,3.6f,"- Your score is determined by how many strokes, it takes you to get your ball");
		drawText(-8.0f,2.8f,"	into the hole, minus the course's set par.");
		drawText(-8.0f,2.0f,"- For this course par is 5.");
		drawText(-8.0f,1.2f,"- Par is the number of strokes a good player should normally require for a course.");
		drawText(-8.0f,0.4f,"- The four purple coloured holes towards the centre of the course are portals.");
		drawText(-8.0f,-0.4f,"- A portal will transport your ball to any of the portals (even your current portal).");
		drawText(-8.0f,-1.2f,"- To enter a portal, simply bit your ball to it, in the same way you'd put your ball");
		drawText(-8.0f,-2.0f,"	(Your exit portal is random).");
		drawText(-8.0f,-2.8f,"- Be careful when entering a portal, you exit a portal just as fast as you entered.");
		drawText(-7.5f,-4.6f,"SCORING");
		drawText(-7.5f,-4.7f,"________");
		drawText(-8.0f,-5.5f,"- Albatross: 3 under par. You're absolutely stunning at crazy golf. Score = -3.");
		drawText(-8.0f,-6.3f,"- Eagle: 2 under par. You're very much exceptional at crazy golf. Score = -2.");
		drawText(-8.0f,-7.1f,"- Birdie: 1 under par. You're pretty remarkable at crazy golf. Score = -1");
		drawText(-8.0f,-7.9f,"- Par: Par. You are very much average at crazy golf. Score = 0");
		drawText(-8.0f,-8.7f,"- Bogie: 1 over par. You're not great at crazy golf. Score = +1");
		drawText(-8.0f,-9.5f,"- Double-Bogie: 2 over par. You're woeful at crazy golf. Score = +2");
		drawText(-8.0f,-10.3f,"- Triple-Bogie: 3 over par. You're utterly atrocious at crazy golf. Score = +3");
		drawText(-8.0f,-11.1f,"- If you happen to put your ball in less than 3 under par strokes, then well done");
		drawText(-8.0f,-11.9f,"	  but there isn't a name for this and your score will be your strokes minus par");
		drawText(-8.0f,-12.7f,"- If you happen to put your ball in more than 3 over par, there isn't a name");
		drawText(-8.0f,-13.5f,"	  for this but it means that you're terrible. Your score will be your strokes minus par.");
	}

	if((Win==true)&&(Help==false))											//if the user has won and they are not in the help menu, text will appear on screen. If they putted in 3 then it'd say they got an eagle,, for example.
	{
		setColour(0.0f,0.0f,0.0f);

		if(Strokes<=(Par-4))
		{
			drawText(-1.7f,0.5f,"@%#& Me!!!! You're ");
			drawText(-1.7f,0.0f,"amazing! Go play a");
			drawText(-1.3f,-0.5f,"harder game.");
		}
		else if(Strokes==(Par-3))
		{
			drawText(-1.1f,0.25f,"Albatross!!!");
			drawText(-1.0f,-0.25f,"Fantastic!.");
		}
		else if(Strokes==(Par-2))
		{
			drawText(-1.35f,0.25f,"Eagle!! You're ");
			drawText(-1.7f,-0.25f,"damn Good at this.");
		}
		else if(Strokes==(Par-1))
		{
			drawText(-1.8f,0.0f,"Birdie! Pretty good.");
		}
		else if(Strokes==(Par))
		{
			drawText(-1.2f,0.0f,"Par. Not bad.");
		}
		else if(Strokes==(Par+1))
		{
			drawText(-0.55f,0.5f,"Bogie.");
			drawText(-1.6f,0.0f,"Going to need to ");
			drawText(-1.8f,-0.5f,"step it up next time.");
		}
		else if(Strokes==(Par+2))
		{
			drawText(-1.4f,0.25f,"Double-Bogie.");
			drawText(-1.7f,-0.25f,"Not good enough.");
		}
		else if(Strokes==(Par+3))
		{
			drawText(-1.2f,0.25f,"Triple-Bogie.");
			drawText(-1.3f,-0.25f,"Wow! Terrible!");
		}
		else if(Strokes>=(Par+4))
		{
			drawText(-1.5f,0.5f,"You're not very");
			drawText(-1.8f,0.0f,"good at is, are you?");
			drawText(-1.2f,-0.5f,"Just give up");
		}
	}
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