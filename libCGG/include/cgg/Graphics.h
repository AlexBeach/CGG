#pragma once
#include "cgg/Matrix2.h"
#include "cgg/Matrix3.h"
#include "cgg/Transform2.h"
#include "cgg/Transform3.h"
#include "cgg/Window.h"
#include <vector>

// some useful constants!
const float PI = 3.1415926535897932384626433832795f;
const float TWO_PI = 6.283185307179586476925286766559f;

/// \brief  specifies the colour of the screen when it is cleared 
/// \param  r red
/// \param  g green
/// \param  b blue
void setBackgroundColour(float r, float g, float b);

//------------------------------------------------------------------------------------------------------------------------------------
// GPU BATCHING FUNCTIONS
//------------------------------------------------------------------------------------------------------------------------------------

/// \brief  Call this to start drawing a shape. Be sure to store the returned integer! (The integer represents the shape once uploaded to the GPU!)
///         This can be used with any of the drawing functions with the exception of the 'drawPrimitives' calls. The returned integer is a 
///         handle to the object on the GPU, and can be passed to any of the drawShape functions to render the stored geometry. 
///         The benefits of this method are that there are a minimal number of functions called on the CPU to render (no function call 
///         overhead, which makes things go a bit quicker!). In addition, because the geometry is resident on the GPU, no time needs 
///         to be wasted sending it to the GPU!
/// \note
/// These funcs allow you to send batches of geometry data to the GPU. The rough process is as follows... 
/// Somewhere, you will need to store a reference to the shape:
/// 
/// \code
/// // This will be used to represent the shape (once it's been uploaded to the GPU)
/// int g_handleToShape = 0;
/// \endcode
/// 
/// At some point (probably during initialisation), you will need to generate the shape data 
///
/// \code 
/// // start sending data to the GPU
/// g_handleToShape = beginShape();
/// 
///   // Any draw calls here, will be batched up and stored on the GPU
/// 
/// // finished buildin the shape!
/// endShape();
/// \endcode
/// 
/// Then when you need to render the data, you will simply need to pass the handle to the GPU using the drawShape method:
/// 
/// \code 
/// drawShape(g_handleToShape);
/// \endcode
int beginShape();

/// \brief  call this to stop drawing a shape
void endShape();

/// \brief  Specify the GPU resident shape to draw (a handle returned from beginShape()). 
/// \param  object the object to draw
void drawShape(int object);

/// \brief  Specify the GPU resident shape to draw (a handle returned from beginShape()) with the specified Matrix2.
/// \param  matrix the transformation matrix for the object being drawn
/// \param  object the object to draw
void drawShape(const Matrix2& matrix, int object);

/// \brief  Specify the GPU resident shape to draw (a handle returned from beginShape()) with the specified Matrix3.
/// \param  matrix the transformation matrix for the object being drawn
/// \param  object the object to draw
void drawShape(const Matrix3& matrix, int object);

//------------------------------------------------------------------------------------------------------------------------------------
// LIGHTING FUNCS
//------------------------------------------------------------------------------------------------------------------------------------

/// \brief  enables a simple light within the scene. The colour specified (with setColour) will control the diffuse colour of the 
///         geometry being rendered. In order to use lighting, you must specify the surface normals. Without these, the surface will 
///         appear black (or simply use whatever normal was last set). Chances are it will look fugly either way!
void enableLighting();

/// \brief  simply disables the lighting 
void disableLighting();

//------------------------------------------------------------------------------------------------------------------------------------
// SIMPLE PRIMITIVE DRAWING FUNCTIONS:
// 
// The following functions allow you to draw some shapes!
//------------------------------------------------------------------------------------------------------------------------------------

/// \brief  specifies the colour to draw (r, g, b, are colour values that go from zero to one!)
/// \param  r red
/// \param  g green
/// \param  b blue
void setColour(float r, float g, float b);

/// \brief  draws a point at the specified location
/// \param  point the point to draw
void drawPoint(const Vec2& point);

/// \brief  draws a point at the specified location
/// \param  point the point to draw
void drawPoint(const Vec3& point);

/// \brief  draws a line betwen the start and end point specified 
/// \param  begin the start of the line
/// \param  end the end of the line
void drawLine(const Vec2& begin, const Vec2& end);

/// \brief  draws a line betwen the start and end point specified 
/// \param  begin the start of the line
/// \param  end the end of the line
void drawLine(const Vec3& begin, const Vec3& end);

/// \brief  draws an array of lines. The number of points should be 2*numLines (since a line has 2 points!)
/// \param  points an array of points to draw 
/// \param  numLines the number of lines to draw
void drawLines(const Vec2 points[], int numLines);

/// \brief  draws an array of lines. The number of points should be 2*numLines (since a line has 2 points!)
/// \param  points an array of points to draw 
/// \param  numLines the number of lines to draw
void drawLines(const Vec3 points[], int numLines);

/// \brief  draws a line between each of the points in sequence.
/// \param  points the points to draw
/// \param  numPoints the number of points to draw
void drawLineStrip(const Vec2 points[], int numPoints);

/// \brief  draws a line between each of the points in sequence.
/// \param  points the points to draw
/// \param  numPoints the number of points to draw
void drawLineStrip(const Vec3 points[], int numPoints);

/// \brief  draws a wireframe polygon between all of the points provided
/// \param  points the points to draw
/// \param  numPoints the number of points to draw
void drawLineLoop(const Vec2 points[], int numPoints);

/// \brief  draws a wireframe polygon between all of the points provided
/// \param  points the points to draw
/// \param  numPoints the number of points to draw
void drawLineLoop(const Vec3 points[], int numPoints);

//------------------------------------------------------------------------------------------------------------------------------------
// GENERIC RENDERING FUNCTIONS
//------------------------------------------------------------------------------------------------------------------------------------

/// \brief  All of the geometry primitives that can be drawn
enum PrimitiveType
{
  kPoints,
  kLines, 
  kTriangles,
  kQuads,
  kWireTriangles,
  kWireQuads,
  kLineLoop,
  kLineStrip
};

/// \brief  begin drawing a set of primitives. This MUST be matched with a call to end() once the drawing has finished.
/// \param  geometryType the type of geometry to draw (one of the PrimitiveType enum values above)
/// \note
/// These functions provide a generic way to draw geometry. Simple call begin() with one the enumeration values contained within 
/// the PrimitiveType enum, add a bunch of vertices, and then finally call end(). For example, to draw a single square:
/// \code
/// begin(kQuads);
///   setNormal( Vec3( 0, 1, 0) );
///   addVertex( Vec3(-1, 0,-1) );
///   addVertex( Vec3( 1, 0,-1) );
///   addVertex( Vec3( 1, 0, 1) );
///   addVertex( Vec3(-1, 0, 1) );
/// end();
/// \endcode
void begin(PrimitiveType geometryType);

  /// \brief  specify a 3D surface normal 
  /// \param  n the surface normal
  void setNormal(const Vec3& n);

  /// \brief  specify a vertex colour
  /// \param  c the surface colour
  void setColour(const Vec3& c);

  /// \brief  specify a vertex value (2D coord X, and Y)
  /// \param  v the vertex position
  void addVertex(const Vec2& v);

  /// \brief  specifiy a 3D vertex value
  /// \param  v the vertex position
  void addVertex(const Vec3& v);

/// \brief  finish drawing primitives
void end();

//------------------------------------------------------------------------------------------------------------------------------------
// VERTEX ARRAY DRAWING FUNCTIONS
//------------------------------------------------------------------------------------------------------------------------------------

/// \brief  vertex + normal structure
struct VertexNormal
{
	Vec3 v; ///< vertex position
	Vec3 n; ///< surface normal
};

/// \brief  vertex + colour structure
struct VertexColour
{
	Vec3 v; ///< vertex position
	Vec3 c; ///< vertex colour
};

/// \brief  vertex + normal + colour structure
struct VertexNormalColour
{
	Vec3 v; ///< vertex position
	Vec3 n; ///< surface normal
	Vec3 c; ///< vertex colour
};

void drawPrimitives(const Vec3 vertices[], int vertex_count, PrimitiveType geometryType);
void drawPrimitives(const VertexNormal vertices[], int vertex_count, PrimitiveType geometryType);
void drawPrimitives(const VertexColour vertices[], int vertex_count, PrimitiveType geometryType);
void drawPrimitives(const VertexNormalColour vertices[], int vertex_count, PrimitiveType geometryType);
void drawPrimitives(const Vec3 vertices[], const int indices[], int index_count, PrimitiveType geometryType);
void drawPrimitives(const VertexNormal vertices[], const int indices[], int index_count, PrimitiveType geometryType);
void drawPrimitives(const VertexColour vertices[], const int indices[],  int index_count, PrimitiveType geometryType);
void drawPrimitives(const VertexNormalColour vertices[], const int indices[], int index_count, PrimitiveType geometryType);

inline void drawPrimitives(const std::vector<Vec3>& vertices, PrimitiveType geometryType) { if(vertices.size()) drawPrimitives(&vertices[0], (int)vertices.size(), geometryType); }
inline void drawPrimitives(const std::vector<VertexNormal>& vertices, PrimitiveType geometryType) { if(vertices.size()) drawPrimitives(&vertices[0], (int)vertices.size(), geometryType); }
inline void drawPrimitives(const std::vector<VertexColour>& vertices, PrimitiveType geometryType) { if(vertices.size()) drawPrimitives(&vertices[0], (int)vertices.size(), geometryType); }
inline void drawPrimitives(const std::vector<VertexNormalColour>& vertices, PrimitiveType geometryType) { if(vertices.size()) drawPrimitives(&vertices[0], (int)vertices.size(), geometryType); }
inline void drawPrimitives(const std::vector<Vec3>& vertices, const std::vector<int>& indices, PrimitiveType geometryType) { if(vertices.size() && indices.size()) drawPrimitives(&vertices[0], &indices[0], (int)indices.size(), geometryType); }
inline void drawPrimitives(const std::vector<VertexNormal>& vertices, const std::vector<int>& indices, PrimitiveType geometryType) { if(vertices.size() && indices.size()) drawPrimitives(&vertices[0], &indices[0], (int)indices.size(), geometryType); }
inline void drawPrimitives(const std::vector<VertexColour>& vertices, const std::vector<int>& indices, PrimitiveType geometryType) { if(vertices.size() && indices.size()) drawPrimitives(&vertices[0], &indices[0], (int)indices.size(), geometryType); }
inline void drawPrimitives(const std::vector<VertexNormalColour>& vertices, const std::vector<int>& indices, PrimitiveType geometryType) { if(vertices.size() && indices.size()) drawPrimitives(&vertices[0], &indices[0], (int)indices.size(), geometryType); }

//------------------------------------------------------------------------------------------------------------------------------------
// MATRIX STACK FUNCTIONS
//------------------------------------------------------------------------------------------------------------------------------------

/// \brief  pushes a new matrix onto the stack
void pushMatrix();

/// \brief  multiplies the current matrix by the specified transform matrix
void multMatrix(const Matrix2& tm);

/// \brief	translates the current matrix by the specified amount
void translate(float x, float y);

/// \brief	scales the current transform by the specified amount
void scale(float x, float y);

/// \brief	translates the current matrix by the specified amount
void translate(const Vec2& offset);

/// \brief	scales the current transform by the specified amount
void scale(const Vec2& size);

/// \brief	rotates the current matrix by the specified amount
void rotate(float radians);

/// \brief  multiplies the current matrix by the specified transform matrix
void multMatrix(const Matrix3& tm);

/// \brief	translates the current matrix by the specified amount
void translate(float x, float y, float z);

/// \brief	scales the current transform by the specified amount
void scale(float x, float y, float z);

/// \brief	translates the current matrix by the specified amount
void translate(const Vec3& offset);

/// \brief	scales the current transform by the specified amount
void scale(const Vec3& size);

/// \brief	rotates the current matrix by the specified angle around the axis provided
void rotate(float radians, const Vec3& axis);

/// \brief  pops a matrix off the stack
void popMatrix();

