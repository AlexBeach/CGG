#pragma once
#include "cgg/Vec2.h"

//------------------------------------------------------------------------------------------------------------------------------------
/// \name   KEYBOARD FUNCTIONS
/// \brief  The following functions control the window properties
//------------------------------------------------------------------------------------------------------------------------------------

enum 
{
  kKeyEnter = 13,
  kKeyBackSpace = 0x08,
  kKeyTab = 0x09,
  kKeyEscape = 0x1B,
  kKeyDelete = 0x7F,
  kKeyF1 = 0x0101,
  kKeyF2 = 0x0102,
  kKeyF3 = 0x0103,
  kKeyF4 = 0x0104,
  kKeyF5 = 0x0105,
  kKeyF6 = 0x0106,
  kKeyF7 = 0x0107,
  kKeyF8 = 0x0108,
  kKeyF9 = 0x0109,
  kKeyF10 = 0x010A,
  kKeyF11 = 0x010B,
  kKeyF12 = 0x010C,
  kKeyLeft = 0x0164,
  kKeyUp = 0x0165,
  kKeyRight = 0x0166,
  kKeyDown = 0x0167,
  kKeyPageUp = 0x0168,
  kKeyPageDown = 0x0169,
  kKeyHome = 0x016A,
  kKeyEnd = 0x016B,
  kKeyInsert = 0x016C
};

/// \brief  returns true if the specified key is pressed
/// \param  key true if the key is pressed.
bool isKeyPressed(short key);

/// \brief	returns true if the shift modifier key is pressed
bool isShiftPressed();

/// \brief	returns true if the alt modifier key is pressed
bool isAltPressed();

/// \brief	returns true if the ctrl modifier key is pressed
bool isCtrlPressed();

//------------------------------------------------------------------------------------------------------------------------------------
/// \name   WINDOW FUNCTIONS
/// \brief  The following functions control the window properties
//------------------------------------------------------------------------------------------------------------------------------------

/// \brief  returns the window width
/// \return the width of the window (in pixels)
int getWindowWidth();

/// \brief  returns the window height
/// \return the height of the window (in pixels)
int getWindowHeight();

/// \brief  resizes the window to the size specified
/// \param  w the window width
/// \param  h the window height
void resizeWindow(int w, int h);

/// \brief  sets the title text of the window
/// \param  title the window title 
void setWindowTitle(const char title[]);

/// \brief  Converts a 2D coordinate from pixel coordinates, to the screen coordinates. By default screen coordinates have the range 
///         [-20, -15] to [20, 15], but those can be changed using the setScreenCoordinates function.
/// \param  x the x coord of the mouse click 
/// \param  y the y coord of the mouse click 
/// \return the coordinate in screen space
Vec2 getScreenCoordinates(int x, int y);

/// \brief  Sets the screen space coordinate system. By default screen coordinates have the range [-20, -15] to [20, 15]. The 
///         getScreenCoordinates function can be used to 
void setScreenCoordinates(float minx, float maxx, float miny, float maxy);


//------------------------------------------------------------------------------------------------------------------------------------
/// \name   MAIN ENTRY POINT
/// \brief  Call this from main to run the app
//------------------------------------------------------------------------------------------------------------------------------------
int runApp();
