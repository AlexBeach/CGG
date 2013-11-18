#include "cgg/Graphics.h"
#include <Windows.h>
#include <cstdint>
#include <time.h>
#include "GL/glut.h"

int _g_currentObject = -1;

int beginShape()
{
	if(_g_currentObject  == -1)
	{
		_g_currentObject  = (int)glGenLists(1);
		glNewList(_g_currentObject, GL_COMPILE);
	}
	return _g_currentObject;
}

/// call this to stop drawing a shape
void endShape()
{
	glEndList();
	_g_currentObject  = -1;
}

void setBackgroundColour(float r, float g, float b)
{
  glClearColor(r, g, b, 0);
}

/// Specify the GPU resident shape to draw (a handle returned from beginShape()). 
void drawShape(int object)
{
	glCallList((unsigned)object);
}

/// call this to draw the object you built! You need to specify a matrix for it, as well as an object ID.
void drawShape(const Matrix2& matrix, int object)
{
	glPushMatrix();
	{
		float m[16] = {0};
		m[0] = matrix.x.x;
		m[1] = matrix.x.y;
		m[4] = matrix.y.x;
		m[5] = matrix.y.y;
		m[10] = 1.0f;
		m[12] = matrix.w.x;
		m[13] = matrix.w.y;
		m[15] = 1.0f;
		glMultMatrixf(m);
		glCallList((unsigned)object);
	}
	glPopMatrix();
}

/// call this to draw the object you built! You need to specify a matrix for it, as well as an object ID.
void drawShape(const Matrix3& matrix, int object)
{
	glPushMatrix();
	{
    multMatrix(matrix);
		glCallList((unsigned)object);
	}
	glPopMatrix();
}
/// specifies the colour to draw (r, g, b, are colour values that go from zero to one!)
void setColour(float r, float g, float b)
{
	glColor3f(r, g, b);
}

/// draws a point at the specified location
void drawPoint(const Vec3& point)
{
	glBegin(GL_POINTS);
	glVertex3f(point.x, point.y, point.z);
	glEnd();
}

/// draws a line at the specified location
void drawLine(const Vec3& begin, const Vec3& end)
{
	glBegin(GL_LINES);
	glVertex3f(begin.x, begin.y, begin.z);
	glVertex3f(end.x, end.y, end.z);
	glEnd();
}

/// draws a point at the specified location
void drawPoint(const Vec2& point)
{
	glBegin(GL_POINTS);
	glVertex3f(point.x, point.y, 0);
	glEnd();
}

/// draws a line at the specified location
void drawLine(const Vec2& begin, const Vec2& end)
{
	glBegin(GL_LINES);
	glVertex3f(begin.x, begin.y, 0);
	glVertex3f(end.x, end.y, 0);
	glEnd();
}

/// draws an array of lines. The number of points should be 2*numLines (since a line has 2 points!)
void drawLines(const Vec2 points[], int numLines)
{
	glBegin(GL_LINES);
	for(int i = 0; i < numLines * 2; ++i)
	{
		glVertex3f(points[i].x, points[i].y, 0);
	}
	glEnd();
}

/// draws a line between each of the points in sequence.
void drawLineStrip(const Vec2 points[], int numPoints)
{
	glBegin(GL_LINE_STRIP);
	for(int i = 0; i < numPoints; ++i)
	{
		glVertex3f(points[i].x, points[i].y, 0);
	}
	glEnd();
}

/// draws a wireframe polygon between all of the points provided
void drawLineLoop(const Vec2 points[], int numPoints)
{
	glBegin(GL_LINE_LOOP);
	for(int i = 0; i < numPoints; ++i)
	{
		glVertex3f(points[i].x, points[i].y, 0);
	}
	glEnd();
}

/// draws an array of lines. The number of points should be 2*numLines (since a line has 2 points!)
void drawLines(const Vec3 points[], int numLines)
{
	glBegin(GL_LINES);
	for(int i = 0; i < numLines * 2; ++i)
	{
		glVertex3f(points[i].x, points[i].y, points[i].z);
	}
	glEnd();
}

/// draws a line between each of the points in sequence.
void drawLineStrip(const Vec3 points[], int numPoints)
{
	glBegin(GL_LINE_STRIP);
	for(int i = 0; i < numPoints; ++i)
	{
		glVertex3f(points[i].x, points[i].y, points[i].z);
	}
	glEnd();
}

/// draws a wireframe polygon between all of the points provided
void drawLineLoop(const Vec3 points[], int numPoints)
{
	glBegin(GL_LINE_LOOP);
	for(int i = 0; i < numPoints; ++i)
	{
		glVertex3f(points[i].x, points[i].y, points[i].z);
	}
	glEnd();
}


void drawPrimitives(const Vec3 vertices[], int vertex_count, PrimitiveType geometryType)
{
	if(vertices && vertex_count)
	{
		GLenum mode = GL_POINTS;
		switch (geometryType)
		{
		case kPoints: mode = GL_POINTS; break;
		case kLines: mode = GL_LINES; break;
		case kTriangles: mode = GL_TRIANGLES; break;
		case kQuads: mode = GL_QUADS; break;
		case kWireTriangles: mode = GL_TRIANGLES; glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
		case kWireQuads: mode = GL_QUADS;  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
		case kLineLoop: mode = GL_LINE_LOOP; break;
		case kLineStrip: mode = GL_LINE_STRIP; break;
		default:
			break;
		}

		glVertexPointer(3, GL_FLOAT, sizeof(Vec3), vertices);
		glEnableClientState(GL_VERTEX_ARRAY);
		glDrawArrays(mode, 0, vertex_count);
		glDisableClientState(GL_VERTEX_ARRAY);

		switch (geometryType)
		{
		case kWireTriangles: mode = GL_TRIANGLES; glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
		case kWireQuads: mode = GL_QUADS;  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
		default: break;
		}
	}
}

void drawPrimitives(const VertexNormal vertices[], int vertex_count, PrimitiveType geometryType)
{
	if(vertices && vertex_count)
	{
		GLenum mode = GL_POINTS;
		switch (geometryType)
		{
		case kPoints: mode = GL_POINTS; break;
		case kLines: mode = GL_LINES; break;
		case kTriangles: mode = GL_TRIANGLES; break;
		case kQuads: mode = GL_QUADS; break;
		case kWireTriangles: mode = GL_TRIANGLES; glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
		case kWireQuads: mode = GL_QUADS;  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
		case kLineLoop: mode = GL_LINE_LOOP; break;
		case kLineStrip: mode = GL_LINE_STRIP; break;
		default:
			break;
		}

		glVertexPointer(3, GL_FLOAT, sizeof(VertexNormal), &vertices->v);
		glEnableClientState(GL_VERTEX_ARRAY);
		glNormalPointer(GL_FLOAT, sizeof(VertexNormal), &vertices->n);
		glEnableClientState(GL_NORMAL_ARRAY);
		glDrawArrays(mode, 0, vertex_count);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);

		switch (geometryType)
		{
		case kWireTriangles: mode = GL_TRIANGLES; glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
		case kWireQuads: mode = GL_QUADS;  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
		default: break;
		}
	}
}

void drawPrimitives(const VertexColour vertices[], int vertex_count, PrimitiveType geometryType)
{
	if(vertices && vertex_count)
	{
		GLenum mode = GL_POINTS;
		switch (geometryType)
		{
		case kPoints: mode = GL_POINTS; break;
		case kLines: mode = GL_LINES; break;
		case kTriangles: mode = GL_TRIANGLES; break;
		case kQuads: mode = GL_QUADS; break;
		case kWireTriangles: mode = GL_TRIANGLES; glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
		case kWireQuads: mode = GL_QUADS;  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
		case kLineLoop: mode = GL_LINE_LOOP; break;
		case kLineStrip: mode = GL_LINE_STRIP; break;
		default:
			break;
		}

		glVertexPointer(3, GL_FLOAT, sizeof(VertexColour), &vertices->v);
		glEnableClientState(GL_VERTEX_ARRAY);
		glColorPointer(3, GL_FLOAT, sizeof(VertexColour), &vertices->c);
		glEnableClientState(GL_COLOR_ARRAY);
		glDrawArrays(mode, 0, vertex_count);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);

		switch (geometryType)
		{
		case kWireTriangles: mode = GL_TRIANGLES; glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
		case kWireQuads: mode = GL_QUADS;  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
		default: break;
		}
	}
}

void drawPrimitives(const VertexNormalColour vertices[], int vertex_count, PrimitiveType geometryType)
{
	if(vertices && vertex_count)
	{
		GLenum mode = GL_POINTS;
		switch (geometryType)
		{
		case kPoints: mode = GL_POINTS; break;
		case kLines: mode = GL_LINES; break;
		case kTriangles: mode = GL_TRIANGLES; break;
		case kQuads: mode = GL_QUADS; break;
		case kWireTriangles: mode = GL_TRIANGLES; glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
		case kWireQuads: mode = GL_QUADS;  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
		case kLineLoop: mode = GL_LINE_LOOP; break;
		case kLineStrip: mode = GL_LINE_STRIP; break;
		default:
			break;
		}

		glVertexPointer(3, GL_FLOAT, sizeof(VertexNormalColour), &vertices->v);
		glEnableClientState(GL_VERTEX_ARRAY);
		glNormalPointer(GL_FLOAT, sizeof(VertexNormalColour), &vertices->n);
		glEnableClientState(GL_NORMAL_ARRAY);
		glColorPointer(3, GL_FLOAT, sizeof(VertexNormalColour), &vertices->c);
		glEnableClientState(GL_COLOR_ARRAY);
		glDrawArrays(mode, 0, vertex_count);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);

		switch (geometryType)
		{
		case kWireTriangles: mode = GL_TRIANGLES; glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
		case kWireQuads: mode = GL_QUADS;  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
		default: break;
		}
	}
}

void drawPrimitives(const Vec3 vertices[], const int indices[], int index_count, PrimitiveType geometryType)
{
	if(vertices && indices && index_count)
	{
		GLenum mode = GL_POINTS;
		switch (geometryType)
		{
		case kPoints: mode = GL_POINTS; break;
		case kLines: mode = GL_LINES; break;
		case kTriangles: mode = GL_TRIANGLES; break;
		case kQuads: mode = GL_QUADS; break;
		case kWireTriangles: mode = GL_TRIANGLES; glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
		case kWireQuads: mode = GL_QUADS;  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
		case kLineLoop: mode = GL_LINE_LOOP; break;
		case kLineStrip: mode = GL_LINE_STRIP; break;
		default:
			break;
		}

		glVertexPointer(3, GL_FLOAT, sizeof(Vec3), vertices);
		glEnableClientState(GL_VERTEX_ARRAY);
		glDrawElements(mode, index_count, GL_UNSIGNED_INT, indices);
		glDisableClientState(GL_VERTEX_ARRAY);

		switch (geometryType)
		{
		case kWireTriangles: mode = GL_TRIANGLES; glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
		case kWireQuads: mode = GL_QUADS;  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
		default: break;
		}
	}
}

void drawPrimitives(const VertexNormal vertices[], const int indices[], int index_count, PrimitiveType geometryType)
{
	if(vertices && indices && index_count)
	{
		GLenum mode = GL_POINTS;
		switch (geometryType)
		{
		case kPoints: mode = GL_POINTS; break;
		case kLines: mode = GL_LINES; break;
		case kTriangles: mode = GL_TRIANGLES; break;
		case kQuads: mode = GL_QUADS; break;
		case kWireTriangles: mode = GL_TRIANGLES; glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
		case kWireQuads: mode = GL_QUADS;  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
		case kLineLoop: mode = GL_LINE_LOOP; break;
		case kLineStrip: mode = GL_LINE_STRIP; break;
		default:
			break;
		}

		glVertexPointer(3, GL_FLOAT, sizeof(VertexNormal), &vertices->v);
		glEnableClientState(GL_VERTEX_ARRAY);
		glNormalPointer(GL_FLOAT, sizeof(VertexNormal), &vertices->n);
		glEnableClientState(GL_NORMAL_ARRAY);
		glDrawElements(mode, index_count, GL_UNSIGNED_INT, indices);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);

		switch (geometryType)
		{
		case kWireTriangles: mode = GL_TRIANGLES; glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
		case kWireQuads: mode = GL_QUADS;  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
		default: break;
		}
	}
}

void drawPrimitives(const VertexColour vertices[], const int indices[],  int index_count, PrimitiveType geometryType)
{
	if(vertices && indices && index_count)
	{
		GLenum mode = GL_POINTS;
		switch (geometryType)
		{
		case kPoints: mode = GL_POINTS; break;
		case kLines: mode = GL_LINES; break;
		case kTriangles: mode = GL_TRIANGLES; break;
		case kQuads: mode = GL_QUADS; break;
		case kWireTriangles: mode = GL_TRIANGLES; glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
		case kWireQuads: mode = GL_QUADS;  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
		case kLineLoop: mode = GL_LINE_LOOP; break;
		case kLineStrip: mode = GL_LINE_STRIP; break;
		default:
			break;
		}

		glVertexPointer(3, GL_FLOAT, sizeof(VertexColour), &vertices->v);
		glEnableClientState(GL_VERTEX_ARRAY);
		glColorPointer(3, GL_FLOAT, sizeof(VertexColour), &vertices->c);
		glEnableClientState(GL_COLOR_ARRAY);
		glDrawElements(mode, index_count, GL_UNSIGNED_INT, indices);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);

		switch (geometryType)
		{
		case kWireTriangles: mode = GL_TRIANGLES; glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
		case kWireQuads: mode = GL_QUADS;  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
		default: break;
		}
	}
}

void drawPrimitives(const VertexNormalColour vertices[], const int indices[], int index_count, PrimitiveType geometryType)
{
	if(vertices && indices && index_count)
	{
		GLenum mode = GL_POINTS;
		switch (geometryType)
		{
		case kPoints: mode = GL_POINTS; break;
		case kLines: mode = GL_LINES; break;
		case kTriangles: mode = GL_TRIANGLES; break;
		case kQuads: mode = GL_QUADS; break;
		case kWireTriangles: mode = GL_TRIANGLES; glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
		case kWireQuads: mode = GL_QUADS;  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
		case kLineLoop: mode = GL_LINE_LOOP; break;
		case kLineStrip: mode = GL_LINE_STRIP; break;
		default:
			break;
		}

		glVertexPointer(3, GL_FLOAT, sizeof(VertexNormalColour), &vertices->v);
		glEnableClientState(GL_VERTEX_ARRAY);
		glNormalPointer(GL_FLOAT, sizeof(VertexNormalColour), &vertices->n);
		glEnableClientState(GL_NORMAL_ARRAY);
		glColorPointer(3, GL_FLOAT, sizeof(VertexNormalColour), &vertices->c);
		glEnableClientState(GL_COLOR_ARRAY);
		glDrawElements(mode, index_count, GL_UNSIGNED_INT, indices);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);

		switch (geometryType)
		{
		case kWireTriangles: mode = GL_TRIANGLES; glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
		case kWireQuads: mode = GL_QUADS;  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
		default: break;
		}
	}
}

void enableLighting()
{
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
}

void disableLighting()
{
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
}


PrimitiveType _g_lastPrimType = kPoints;

/// \brief  begin drawing a set of primitives. This MUST be matched with a call to end() once the drawing has finished.
/// \param  geometryType the type of geometry to draw (one of the PrimitiveType enum values above)
void begin(PrimitiveType geometryType)
{
		GLenum mode = GL_POINTS;
		switch (geometryType)
		{
		case kPoints: mode = GL_POINTS; break;
		case kLines: mode = GL_LINES; break;
		case kTriangles: mode = GL_TRIANGLES; break;
		case kQuads: mode = GL_QUADS; break;
		case kWireTriangles: mode = GL_TRIANGLES; glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
		case kWireQuads: mode = GL_QUADS;  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); break;
		case kLineLoop: mode = GL_LINE_LOOP; break;
		case kLineStrip: mode = GL_LINE_STRIP; break;
		default:
			break;
		}
    _g_lastPrimType = geometryType;
    glBegin(mode);
}

/// \brief  specify a 3D surface normal 
/// \param  n the surface normal
void setNormal(const Vec3& n)
{
  glNormal3fv(&n.x);
}

/// \brief  specify a vertex colour
/// \param  c the surface colour
void setColour(const Vec3& c)
{
  glColor3fv(&c.x);
}

/// \brief  specify a vertex value (2D coord X, and Y)
/// \param  v the vertex position
void addVertex(const Vec2& v)
{
  glVertex2fv(&v.x);
}

/// \brief  specifiy a 3D vertex value
/// \param  v the vertex position
void addVertex(const Vec3& v)
{
  glVertex3fv(&v.x);
}

/// \brief  finish drawing primitives
void end()
{
  glEnd();
	GLenum mode;
	switch (_g_lastPrimType)
	{
	case kWireTriangles: mode = GL_TRIANGLES; glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
	case kWireQuads: mode = GL_QUADS;  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); break;
	default:
		break;
	}
}