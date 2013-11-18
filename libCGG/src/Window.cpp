#include "cgg/Graphics.h"
#include "cgg/Window.h"
#include <Windows.h>
#include <cstdint>
#include <time.h>
#include "GL/glut.h"

// declared in main.cpp
extern void init();
extern void update(float dt);
extern void draw();
extern void draw3D();
extern void mouseMove(int w, int h);
extern void mousePress(int w, int h);
extern void mouseRelease(int w, int h);

float zoom = 15.0f;
float rotx = 0;
float roty = 0.001f;
float tx = 0;
float ty = 0;
int lastx=0;
int lasty=0;
unsigned char Buttons[3] = {0};
bool rotating = false;
bool _g_mayaCamEnabled = true;
extern void draw3D();

// current state of the keyboard
bool g_keys[512] = {false};
int g_modifiers = 0;

/// \brief	returns true if the shift modifier key is pressed
bool isShiftPressed()
{
	return (g_modifiers & GLUT_ACTIVE_SHIFT) != 0;
}

/// \brief	returns true if the alt modifier key is pressed
bool isAltPressed()
{
	return (g_modifiers & GLUT_ACTIVE_ALT) != 0;
}

/// \brief	returns true if the ctrl modifier key is pressed
bool isCtrlPressed()
{
	return (g_modifiers & GLUT_ACTIVE_CTRL) != 0;
}

// called when key is pressed
void onKeyPress(unsigned char k, int, int)
{
	g_modifiers = glutGetModifiers();
	g_keys[k] = true;
}

// called when key is released
void onKeyRelease(unsigned char k, int, int)
{
	g_modifiers = glutGetModifiers();
	g_keys[k] = false;
}

// called when key is pressed
void onSpecialKeyPress(int k, int, int)
{
	g_modifiers = glutGetModifiers();
	g_keys[k + 256] = true;
}

// called when key is released
void onSpecialKeyRelease(int k, int, int)
{
	g_modifiers = glutGetModifiers();
	g_keys[k + 256] = false;
}

// used to return the state of a key to main.cpp
bool isKeyPressed(short key)
{
	return g_keys[key];
}

// some variables used to time each frame
float	g_startOfFrame, g_endOfFrame, g_rateInv;
int64_t g_startClk;

// initialise the frame tmer
void initFrameTimer()
{
	int64_t rate;
	g_rateInv = 1.0f/(float)CLOCKS_PER_SEC;

	if(!QueryPerformanceFrequency((LARGE_INTEGER*)&rate) )
		return;

	if(!rate)
		return;

	g_rateInv=1.0f / (float)rate;
	if(!QueryPerformanceCounter((LARGE_INTEGER*)&g_startClk))
		return;
}

// returns the current frame time
float currentTime()
{
	int64_t endClk;
	QueryPerformanceCounter((LARGE_INTEGER*)&endClk);
	return (endClk - g_startClk) * g_rateInv;
}

// called when glut has run out of messages to process
void onIdle()
{
	// determine amount of seconds since the last update
	do
	{
		g_endOfFrame = currentTime();
	}
	while(g_endOfFrame == g_startOfFrame);

	// time increment
	float dt = g_endOfFrame - g_startOfFrame;
	g_startOfFrame = g_endOfFrame;

	// do user update
	update(dt);

	// ask glut to redraw the screen when this function has completed
	glutPostRedisplay();
}

int g_w = 800, g_h = 600;

// return the window width
int getWindowWidth()
{
	return g_w;
}

// return the window height
int getWindowHeight()
{
	return g_h;
}

float g_2DCoords[4] = {-20.0f, 20.0f, -15.0f, 15.0f};

void setScreenCoordinates(float minx, float maxx, float miny, float maxy)
{
	g_2DCoords[0] = minx;
	g_2DCoords[1] = maxx;
	g_2DCoords[2] = miny;
	g_2DCoords[3] = maxy;
}

//------------------------------------------------------------------------------------------------------------------------------------
/// Converts x and y window coordinates (0 to 800, 0 to 600) into screen coordinates (-20 to 20, -15 to 15)
//------------------------------------------------------------------------------------------------------------------------------------
Vec2 getScreenCoordinates(int x, int y)
{
	float w = (float)getWindowWidth();
	float h = (float)getWindowHeight();
	Vec2 p;
	p.x = (x / w) * (g_2DCoords[1] - g_2DCoords[0]) + g_2DCoords[0];
	p.y = (y / h) * (g_2DCoords[3] - g_2DCoords[2]) + g_2DCoords[2];
	return p;
}

// called when the screen needs to be redrawn
void onDraw()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, g_w, g_h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, (float)g_w / g_h, 0.1f, 150.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0,0,-zoom);
	glTranslatef(tx,ty,0);
	glRotatef(rotx,1,0,0);
	glRotatef(roty,0,1,0);

  glEnable(GL_DEPTH_TEST);
	// perform user drawing
	draw3D();
  glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(g_2DCoords[0], g_2DCoords[1], g_2DCoords[2], g_2DCoords[3], -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// perform user drawing
	draw();
	glutSwapBuffers();
}

// called when the window changes size
void onReshape(int w, int h)
{
	g_w = w;
	g_h = h ? h : 1;
}


/// \brief  resizes the window to the size specified
/// \param  w the window width
/// \param  h the window height
void resizeWindow(int w, int h)
{
	g_w = w;
	g_h = h;
	glutReshapeWindow(w, h);
}

/// \brief  sets the title text of the window
/// \param  title the window title 
void setWindowTitle(const char title[])
{
	glutSetWindowTitle(title);
}

void onMouseMove(int x, int y)
{
	g_modifiers = glutGetModifiers();
	if(rotating && _g_mayaCamEnabled)
	{
		int diffx = x - lastx;
		int diffy = y - lasty;
		lastx = x;
		lasty = y;
		if(Buttons[2] || (Buttons[0] && Buttons[1]))
		{
			zoom -= (float) 0.05f * diffx;
		}
		else
		if(Buttons[0])
		{
			rotx += (float) 0.5f * diffy;
			roty += (float) 0.5f * diffx;
		}
		else
		if(Buttons[1])
		{
			tx += (float) 0.05f * diffx;
			ty -= (float) 0.05f * diffy;
		}
	}
	else
	{
		mouseMove(x, g_h - y);
	}
}

void onMouseButton(int button, int state, int w, int h)
{
	g_modifiers = glutGetModifiers();
	// store button state
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		Buttons[0] = state == GLUT_DOWN;
		break;
	case GLUT_MIDDLE_BUTTON:
		Buttons[1] = state == GLUT_DOWN;
		break;
	case GLUT_RIGHT_BUTTON:
		Buttons[2] = state == GLUT_DOWN;
		break;
	default:
		break;
	}
	lastx = w;
	lasty = h;

	// if entering rotation mode
	if(state == GLUT_DOWN && (g_modifiers & GLUT_ACTIVE_ALT))
	{
		rotating = true;
	}
	else
	if(rotating)
	{
		rotating = Buttons[0] || Buttons[1] || Buttons[2];
	}
	else
	if(button == GLUT_LEFT_BUTTON)
	{
		if(state == GLUT_DOWN)
		{
			mousePress(w, g_h - h);
		}
		else
		{
			mouseRelease(w, g_h - h);
		}
	}
}

// the main entry point
int runApp()
{
  char* foo[] = {"foo.exe", 0};
  int argc = 1;
	glutInit(&argc, foo);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3D Maths is even cooler....");
	glutDisplayFunc(onDraw);
	glutReshapeFunc(onReshape);
	glutIdleFunc(onIdle);
	glutKeyboardFunc(onKeyPress);
	glutKeyboardUpFunc(onKeyRelease);
	glutSpecialFunc(onSpecialKeyPress);
	glutSpecialUpFunc(onSpecialKeyRelease);
	glutMouseFunc(onMouseButton);
	glutMotionFunc(onMouseMove);
	// user init
	init();
	initFrameTimer();
	// run app
	glutMainLoop();
	return 0;
}
