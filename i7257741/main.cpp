#include "cgg/Graphics.h"
#include <iostream>
//#define WIN_32_LEAN_AND_MEAN
#include <windows.h>
//#include <GL/GL.h>

float g_time=0,GolfClubAim=0,BallPower=1;
bool CanMove=true,PowerUp=false,SpaceKeyRelease=false;
Matrix2 GolfCoursePos,GolfCourseExtra1Pos,GolfCourseExtra2Pos,TreePos,HoleWinPos,
GolfBallPos,GolfClubofSortsPos,HolePortal1Pos,HolePortal2Pos,HolePortal3Pos,HolePortal4Pos,
PowerBarOuterPos,PowerBarInner1Pos,PowerBarInner2Pos,PowerBarInner3Pos,PowerBarInner4Pos,
PowerBarInner5Pos;
int GolfCourse,GolfCourseExtra1,GolfCourseExtra2,Tree,HoleWin,GolfBall,GolfClubofSorts,
Score=0,Strokes=0,HolePortal1,HolePortal2,HolePortal3,HolePortal4,PowerBarOuter,
PowerBarInner1,PowerBarInner2,PowerBarInner3,PowerBarInner4,PowerBarInner5;

float FindIntersect(Vec2 P,Vec2 D,Vec2 A,Vec2 B)
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

//Matrix2 InverseMatrix(Matrix2 InverseMatrixMatrix)
//{
//	float AD=InverseMatrixMatrix.x.x*InverseMatrixMatrix.y.y;
//	float BC=InverseMatrixMatrix.x.y*InverseMatrixMatrix.y.x;
//
//	Matrix2 Temp;
//
//	Temp.x.x=InverseMatrixMatrix.x.x;
//	Temp.x.y=-InverseMatrixMatrix.x.y;
//	Temp.y.x=-InverseMatrixMatrix.y.x;
//	Temp.y.y=InverseMatrixMatrix.y.y;
//		
//	Temp.w=InverseMatrixMatrix.w;
//	Temp.w=((1/(AD-BC))*(Temp.w));
//	/*Temp.y*=(1/(AD-BC));*/
//
//	return Temp;
//}

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
	//Vec2 (-2.0f,-1.0f),		//69=Fin
};

Vec2 GolfCourseExtra1Points[] = 
{
	Vec2 (-2.0f,7.0f),
	Vec2 (0.0f,8.0f),
	Vec2 (1.0f,10.0f),
	Vec2 (3.0f,10.0f),
	Vec2 (3.0f,6.0f),		//5
	Vec2 (-2.0f,6.0f),
	Vec2 (-2.0f,7.0f),		//7=Fin
};

Vec2 GolfCourseExtra2Points[] = 
	{
		Vec2 (5.0f,5.0f),
		Vec2 (7.0f,5.0f),
		Vec2 (7.0f,4.0f),
		Vec2 (5.0f,4.0f),
		Vec2 (5.0f,5.0f),	//5 and 5=Fin
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
	drawLineLoop(GolfCoursePoints,68);

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

	HoleWin=beginShape();

	for(float angle = -PI; angle <= PI; angle += 0.05)
	{
		Vec2 p(cos(angle)/3, sin(angle)/3);
		setColour(0.0f,0.0f,0.0f);
		drawPoint(p);
	}

	endShape();

	HoleWinPos.w.x=-3.0f;
	HoleWinPos.w.y=-11.0f;

	HolePortal1=beginShape();

	for(float angle = -PI; angle <= PI; angle += 0.05)
	{
		Vec2 p(cos(angle)/3, sin(angle)/3);
		setColour(1.0f,0.0f,1.0f);
		drawPoint(p);
	}

	endShape();

	HolePortal1Pos.w.x=0.0f;
	HolePortal1Pos.w.y=1.55f;

	HolePortal2=beginShape();

	for(float angle = -PI; angle <= PI; angle += 0.05)
	{
		Vec2 p(cos(angle)/3, sin(angle)/3);
		setColour(1.0f,0.0f,1.0f);
		drawPoint(p);
	}

	endShape();

	HolePortal2Pos.w.x=2.6f;
	HolePortal2Pos.w.y=0.0f;

	HolePortal3=beginShape();

	for(float angle = -PI; angle <= PI; angle += 0.05)
	{
		Vec2 p(cos(angle)/3, sin(angle)/3);
		setColour(1.0f,0.0f,1.0f);
		drawPoint(p);
	}

	endShape();

	HolePortal3Pos.w.x=0.0f;
	HolePortal3Pos.w.y=-1.55f;

	HolePortal4=beginShape();

	for(float angle = -PI; angle <= PI; angle += 0.05)
	{
		Vec2 p(cos(angle)/3, sin(angle)/3);
		setColour(1.0f,0.0f,1.0f);
		drawPoint(p);
	}

	endShape();

	HolePortal4Pos.w.x=-2.6f;
	HolePortal4Pos.w.y=0.0f;

	//For the arrow to show the current angle that the ball's direction will go in
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
		if(isKeyPressed('d')||(isKeyPressed('D')))
		{
			GolfClubAim-=(AimSpeed/3.5);
		}

		//Rotate ship left
		if(isKeyPressed('a')||(isKeyPressed('A')))
		{
			GolfClubAim+=(AimSpeed/3.5);
		}
	}
	else
	{
		if((isKeyPressed(' ')==false)&&(SpaceKeyRelease==false))
		{
			SpaceKeyRelease=true;
		}

		/*if(BallPower>0)
		{*/
			if(SpaceKeyRelease==true)
			{
				GolfBallPos.w=GolfBallPos.w+GolfBallPos.y*(BallPower*dt);
				PowerBarOuterPos.w=GolfBallPos.w+GolfBallPos.y*(BallPower*dt);
				PowerBarInner1Pos.w=GolfBallPos.w+GolfBallPos.y*(BallPower*dt);
				PowerBarInner2Pos.w=GolfBallPos.w+GolfBallPos.y*(BallPower*dt);
				PowerBarInner3Pos.w=GolfBallPos.w+GolfBallPos.y*(BallPower*dt);
				PowerBarInner4Pos.w=GolfBallPos.w+GolfBallPos.y*(BallPower*dt);
				PowerBarInner5Pos.w=GolfBallPos.w+GolfBallPos.y*(BallPower*dt);
				BallPower-=2*dt;
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
		/*}*/

		/*if(BallPower<0)
		{
			if(SpaceKeyRelease==true)
			{
				GolfBallPos.w=GolfBallPos.w+GolfBallPos.y*(BallPower*dt);
				PowerBarOuterPos.w=GolfBallPos.w+GolfBallPos.y*(BallPower*dt);
				PowerBarInner1Pos.w=GolfBallPos.w+GolfBallPos.y*(BallPower*dt);
				PowerBarInner2Pos.w=GolfBallPos.w+GolfBallPos.y*(BallPower*dt);
				PowerBarInner3Pos.w=GolfBallPos.w+GolfBallPos.y*(BallPower*dt);
				PowerBarInner4Pos.w=GolfBallPos.w+GolfBallPos.y*(BallPower*dt);
				PowerBarInner5Pos.w=GolfBallPos.w+GolfBallPos.y*(BallPower*dt);
				BallPower+=2*dt;
			}
			else
			{
				if(BallPower>=-20)
				{
					BallPower=BallPower-0.2;
				}
			}

			if(BallPower>=0)
			{
				CanMove=true;
				GolfClubofSortsPos=GolfBallPos;
			}
		}*/
	}

	if((isKeyPressed(' ')==true)&&(CanMove==true))
	{
		GolfBallPos=GolfClubofSortsPos;
		BallPower=1;
		CanMove=false;
		SpaceKeyRelease=false;
	}

	float Closest1=10000.0f;

	Vec2 N1;

	for(int i=1;i<sizeof(GolfCoursePoints)/sizeof(Vec2);i++)
	{
		// These are the same two coordinates used to draw the line. 
		float Isect=FindIntersect(GolfBallPos.w,GolfBallPos.y,GolfCoursePoints[i-1],GolfCoursePoints[i]);

		// if intersection found (e.g. distance returned is not negative!)
		if(Isect>=0)
		{
			if(Isect<Closest1)
			{
				Closest1=Isect;
				Vec2 AB(GolfCoursePoints[i-1]-GolfCoursePoints[i]);
				AB=normalize(AB);
				N1.x=-AB.y;
				N1.y=AB.x;
			}
		}
	}

	float Closest2=10000.0f;

	Vec2 N2;

	for(int i=1;i<sizeof(GolfCourseExtra1Points)/sizeof(Vec2);i++)
	{
		// These are the same two coordinates used to draw the line. 
		float Isect=FindIntersect(GolfBallPos.w,GolfBallPos.y,GolfCourseExtra1Points[i-1],GolfCourseExtra1Points[i]);

		// if intersection found (e.g. distance returned is not negative!)
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

	for(int i=1;i<sizeof(GolfCourseExtra2Points)/sizeof(Vec2);i++)
	{
		// These are the same two coordinates used to draw the line. 
		float Isect=FindIntersect(GolfBallPos.w,GolfBallPos.y,GolfCourseExtra2Points[i-1],GolfCourseExtra2Points[i]);

		// if intersection found (e.g. distance returned is not negative!)
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

	if(Closest1<(BallPower*dt))
	{
		GolfBallPos.y-=2*dot(N1,GolfBallPos.y)*N1;
		GolfBallPos.x.x=GolfBallPos.y.y;
		GolfBallPos.x.y=-GolfBallPos.y.x;
	}

	if(Closest2<(BallPower*dt))
	{
		GolfBallPos.y-=2*dot(N2,GolfBallPos.y)*N2;
		GolfBallPos.x.x=GolfBallPos.y.y;
		GolfBallPos.x.y=-GolfBallPos.y.x;
	}

	if(Closest3<(BallPower*dt))
	{
		GolfBallPos.y-=2*dot(N3,GolfBallPos.y)*N3;
		GolfBallPos.x.x=GolfBallPos.y.y;
		GolfBallPos.x.y=-GolfBallPos.y.x;
	}

	////Loop through each line that makes up the wall
	//for(int i=1;i<sizeof(GolfCoursePoints)/sizeof(Vec2);i++)
	//{
	//	float isect=FindIntersect(GolfBallPos.w,GolfBallPos.y,GolfCoursePoints[i-1],GolfCoursePoints[i]);
	//	
	//	//If intersection found (e.g. distance returned is not negative)
	//	if(isect>=0)
	//	{
	//		//We only care about the closest intersection
	//		if(isect<=0.2f)
	//		{
	//			GolfBallPos=InverseMatrix(GolfBallPos);
	//			/*BallPower*=-BallPower;*/
	//		}
	//	}
	//}

	//for(int i=1;i<sizeof(GolfCourseExtra1Points)/sizeof(Vec2);i++)
	//{
	//	float isect=FindIntersect(GolfBallPos.w,GolfBallPos.y,GolfCourseExtra1Points[i-1],GolfCourseExtra1Points[i]);
	//	
	//	//If intersection found (e.g. distance returned is not negative)
	//	if(isect>=0)
	//	{
	//		//We only care about the closest intersection
	//		if(isect<=0.2f)
	//		{
	//			GolfBallPos=InverseMatrix(GolfBallPos);
	//			/*BallPower*=-BallPower;*/
	//		}
	//	}
	//}

	//for(int i=1;i<sizeof(GolfCourseExtra2Points)/sizeof(Vec2);i++)
	//{
	//	float isect=FindIntersect(GolfBallPos.w,GolfBallPos.y,GolfCourseExtra2Points[i-1],GolfCourseExtra2Points[i]);
	//	
	//	//If intersection found (e.g. distance returned is not negative)

	//	if(isect>=0)
	//	{
	//		//We only care about the closest intersection
	//		if(isect<=0.2f)
	//		{
	//			GolfBallPos=InverseMatrix(GolfBallPos);
	//			/*BallPower*=-BallPower;*/
	//		}
	//	}
	//}

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
	/*glLineWidth(4.0);*/

	drawShape(GolfCoursePos,GolfCourse);
	drawShape(GolfCourseExtra1Pos,GolfCourseExtra1);
	drawShape(GolfCourseExtra2Pos,GolfCourseExtra2);
	drawShape(TreePos,Tree);
	drawShape(HoleWinPos,HoleWin);
	drawShape(HolePortal1Pos,HolePortal1);
	drawShape(HolePortal2Pos,HolePortal2);
	drawShape(HolePortal3Pos,HolePortal3);
	drawShape(HolePortal4Pos,HolePortal4);
	if(CanMove==true)
	{
		drawShape(GolfClubofSortsPos,GolfClubofSorts);
	}
	if((isKeyPressed(' ')==true)&&(SpaceKeyRelease==false))
	{
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
	drawShape(GolfBallPos,GolfBall);
	drawText(-19.5f,15.2f,"Score: %i",Score);
	drawText(-19.5f,14.7f,"Strokes: %i",Strokes);
	drawText(13.4f,15.2f,"Press 'a' to turn anti-clockwise");
	drawText(14.4f,14.7f,"Press 'd' to turn clockwise");
	drawText(9.5f,14.2f,"Press and hold the Space key to increase the power");
	drawText(11.7f,13.7f,"Release the Space key to hit the golf ball");
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