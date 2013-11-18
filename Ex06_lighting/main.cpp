#include "cgg/Graphics.h"
#include <iostream>

bool g_displayNormals = false;
bool g_manualLighting = false;
float g_timer = 0;

// If we want to draw geometry using lighting, then for each vertex, we must also specify a 'surface normal' at that point.
// The surface normal is simply a unit-length vector that describes the surface direction. 
// The following array of data specifies all of the vertices + normals for a single cube. 
// On each line, the vertex is listed first, and the vertex normal is listed second. If you look at the normals for one of 
// the faces (for example, +ve Z), you'll notice the normals all face in the same direction (so for the +ve Z face, all 
// vertex normals point down +ve Z). 
// 
// The vertex normals are only used to perform lighting calculations. Typically most shaders will refer to the normal as 'N'.
// Usually you then have a second unit length vector from the vertex to the light, known as 'L'. 
// 
// The dot product between N and L will allow us to compute the angle between the two vectors:
// 
//   N.L == |L||N|cos(angle)
//
// Since N and L are unit length, we can ignore the magnitudes of the vectors, and the equation simplifies to:
// 
//   N.L == cos(angle)
//
// We don't usually need to know the angle itself, since the cosine gives us a nice falloff curve. So... 
//
//   When N and L face in the same direction, we get a maximum diffuse term of '1' (which we multiply by the colour). 
//   When N and L are at right angles, we get a diffuse term of '0'. 
//   When N . L is negative, the surface is pointing away from the light, and so the surface is in shadow!
// 
// I've added some code to display the normals (which you can toggle on/off by pressing the 'n' key when the app is running). 
// 
// I've also added some horrific code to manually perform the lighting calculation manually (by using vertexc colours!). 
// Pressing the 'L' key toggles this on an off. 
// Manually calculating the lighting isn't a great idea, since the GPU can perform this calculation much quicker than we can!
// There are however occasions where pre-calculating the lighting may be useful - for example, we can use pre-bake insanely 
// complicated lighting models into static environment geometry (often this is baked into textures!). 
//
VertexNormal g_pointsVN[] = 
{
  // +ve Z
  { Vec3(-1.0f, -1.0f, 1.0f), Vec3(0.0f, 0.0f, 1.0f) },
  { Vec3( 1.0f, -1.0f, 1.0f), Vec3(0.0f, 0.0f, 1.0f) },
  { Vec3( 1.0f,  1.0f, 1.0f), Vec3(0.0f, 0.0f, 1.0f) },
  { Vec3(-1.0f,  1.0f, 1.0f), Vec3(0.0f, 0.0f, 1.0f) },
  
  // -ve Z
  { Vec3(-1.0f,  1.0f, -1.0f), Vec3(0.0f, 0.0f, -1.0f) },
  { Vec3( 1.0f,  1.0f, -1.0f), Vec3(0.0f, 0.0f, -1.0f) },
  { Vec3( 1.0f, -1.0f, -1.0f), Vec3(0.0f, 0.0f, -1.0f) },
  { Vec3(-1.0f, -1.0f, -1.0f), Vec3(0.0f, 0.0f, -1.0f) },
  
  // +ve Y
  { Vec3(-1.0f, 1.0f,-1.0f), Vec3(0.0f, 1.0f, 0.0f) },
  { Vec3(-1.0f, 1.0f, 1.0f), Vec3(0.0f, 1.0f, 0.0f) },
  { Vec3( 1.0f, 1.0f, 1.0f), Vec3(0.0f, 1.0f, 0.0f) },
  { Vec3( 1.0f, 1.0f,-1.0f), Vec3(0.0f, 1.0f, 0.0f) },
  
  // -ve Y
  { Vec3( 1.0f, -1.0f, -1.0f), Vec3(0.0f, -1.0f, 0.0f) },
  { Vec3( 1.0f, -1.0f,  1.0f), Vec3(0.0f, -1.0f, 0.0f) },
  { Vec3(-1.0f, -1.0f,  1.0f), Vec3(0.0f, -1.0f, 0.0f) },
  { Vec3(-1.0f, -1.0f, -1.0f), Vec3(0.0f, -1.0f, 0.0f) },
  
  // +ve X
  { Vec3(1.0f, -1.0f,-1.0f), Vec3(1.0f, 0.0f, 0.0f) },
  { Vec3(1.0f, -1.0f, 1.0f), Vec3(1.0f, 0.0f, 0.0f) },
  { Vec3(1.0f,  1.0f, 1.0f), Vec3(1.0f, 0.0f, 0.0f) },
  { Vec3(1.0f,  1.0f,-1.0f), Vec3(1.0f, 0.0f, 0.0f) },
  
  // -ve X
  { Vec3(-1.0f,  1.0f, -1.0f), Vec3(-1.0f, 0.0f, 0.0f) },
  { Vec3(-1.0f,  1.0f,  1.0f), Vec3(-1.0f, 0.0f, 0.0f) },
  { Vec3(-1.0f, -1.0f,  1.0f), Vec3(-1.0f, 0.0f, 0.0f) },
  { Vec3(-1.0f, -1.0f, -1.0f), Vec3(-1.0f, 0.0f, 0.0f) }
};

//------------------------------------------------------------------------------------------------------------------------------------
// called when we initialise the app
//------------------------------------------------------------------------------------------------------------------------------------
void init()
{
  setWindowTitle("'N' toggles display of normals. 'L' toggles GPU/manual lighting calculation");
}

//------------------------------------------------------------------------------------------------------------------------------------
// called when we need to update the app. 'dt' is the time delta (the number of seconds since the last frame)
//------------------------------------------------------------------------------------------------------------------------------------
void update(float dt)
{
	g_timer += dt;

  if(g_timer > 0.5f && isKeyPressed('n')) 
  {
    g_timer = 0;
    g_displayNormals = !g_displayNormals;
  }
  if(g_timer > 0.5f && isKeyPressed('l')) 
  {
    g_timer = 0;
    g_manualLighting = !g_manualLighting;
  }
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
  
  // If using the GPU to compute the lighting (which is what you want to do!)
  if(!g_manualLighting)
  {
    // turn on lighting
    enableLighting();

      // set the diffuse material colour (this will be modulated by the effect of the lighting)
	    setColour(1.0f, 1.0f, 1.0f);

      // draw the cube geometry
      drawPrimitives(g_pointsVN, 24, kQuads);

    // turn off lighting
    disableLighting();
  }
  else
  {
    // otherwise, compute the lighting manually. Don't ever do this in practice! It's insane! (But it may be useful for educational purposes)

    // The direction from the vertex to the light (effectively sunlight in this case!).
    Vec3 L(-0.6f, 1.0f, -0.2f);

    // make sure L has been normalised!
    L = normalize(L);
    
    // start drawing some quads
    begin(kQuads);

    // loop through each vertex normal
    for(int i = 0; i < 24; ++i)
    {
      // compute N.L
      // Make sure we clamp this to zero (so that we ignore any negative values).
      float N_dot_L = std::max(dot(L, g_pointsVN[i].n), 0.0f);

      // the ambient material colour (always gets added to the final colour)
      Vec3 Ka(0.2f, 0.2f, 0.2f);

      // the diffuse material colour
      Vec3 Kd(1.0f, 1.0f, 1.0f);

      // Compute the final colour
      Vec3 colour = Ka + (Kd * N_dot_L);

      // set the vertex colour 
      setColour(colour);

      // specify the vertex
      addVertex(g_pointsVN[i].v);
    }

    // finish drawing our quads
    end();
  }

  // if we are displaying normals
  if(g_displayNormals)
  {
    // make colour pink
	  setColour(1.0f, 0.0f, 1.0f);

    // loop through each vertex
    for(int i = 0; i < 24; ++i)
    {
      // compute an offset (along the normal direction) from the vertex
      Vec3 pn = g_pointsVN[i].v + (g_pointsVN[i].n * 0.2f);

      // draw a line to show the normal
      drawLine(g_pointsVN[i].v, pn);
    }
  }
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
