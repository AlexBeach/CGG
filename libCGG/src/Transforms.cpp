#include "GL/glut.h"
#include "cgg/Matrix3.h"
const float PI = 3.1415926535897932384626433832795f;

void pushMatrix()
{
	glPushMatrix();
}

void multMatrix(const Matrix3& tm)
{
	float gltm[16] = {0};
	gltm[0] = tm.x.x;
	gltm[1] = tm.x.y;
	gltm[2] = tm.x.z;
	gltm[4] = tm.y.x;
	gltm[5] = tm.y.y;
	gltm[6] = tm.y.z;
	gltm[8] = tm.z.x;
	gltm[9] = tm.z.y;
	gltm[10] = tm.z.z;
	gltm[12] = tm.w.x;
	gltm[13] = tm.w.y;
	gltm[14] = tm.w.z;
	gltm[15] = 1.0f;
	glMultMatrixf(gltm);
}

void multMatrix(const Matrix2& tm)
{
	float gltm[16] = {0};
	gltm[0] = tm.x.x;
	gltm[1] = tm.x.y;
	gltm[4] = tm.y.x;
	gltm[5] = tm.y.y;
	gltm[12] = tm.w.x;
	gltm[13] = tm.w.y;
	gltm[15] = 1.0f;
	glMultMatrixf(gltm);
}

void translate(const Vec2& offset)
{
	glTranslatef(offset.x, offset.y, 0);
}

void translate(const Vec3& offset)
{
	glTranslatef(offset.x, offset.y, offset.z);
}

void translate(float x, float y, float z)
{
	glTranslatef(x, y, z);
}

void scale(float x, float y, float z)
{
	glScalef(x, y, z);
}

void translate(float x, float y)
{
	glTranslatef(x, y, 0);
}

void scale(float x, float y)
{
	glScalef(x, y, 1.0f);
}

void scale(const Vec3& size)
{
	glScalef(size.x, size.y, size.z);
}

void scale(const Vec2& size)
{
	glScalef(size.x, size.y, 1.0f);
}

void rotate(float radians, const Vec3& axis)
{
	glRotatef(radians * 180.0f/PI, axis.x, axis.y, axis.z);
}

void rotate(float radians)
{
	glRotatef(radians * 180.0f/PI, 0, 0, 1.0f);
}

void popMatrix()
{
	glPopMatrix();
}
