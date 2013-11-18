#include "cgg/Graphics.h"
#include <iostream>

//
// This app simply tests every single maths function to make sure it *actually* works! 
// Nothing clever here. If the tests pass, nothing is printed. If a test fails, the line 
// number that failed will be written out. 
//

//------------------------------------------------------------------------------------------------------------------------------
// A bunch of functions used to compare floats, Vectors, Matrices and Transforms.
//------------------------------------------------------------------------------------------------------------------------------
bool compare(float a, float b)
{
  return fabs(a - b) < 0.0001f;
}

bool compare(Vec2 a, Vec2 b)
{
  return fabs(a.x - b.x) < 0.0001f && fabs(a.y - b.y) < 0.0001f;
}

bool compare(Vec3 a, Vec3 b)
{
  return fabs(a.x - b.x) < 0.0001f && fabs(a.y - b.y) < 0.0001f && fabs(a.z - b.z) < 0.0001f;
}

bool compare(Matrix2 a, Matrix2 b)
{
  return compare(a.x, b.x) && compare(a.y, b.y) && compare(a.w, b.w);
}

bool compare(Matrix3 a, Matrix3 b)
{
  return compare(a.x, b.x) && compare(a.y, b.y) && compare(a.z, b.z) && compare(a.w, b.w);
}

bool compare(Transform2 a, Transform2 b)
{
  return compare(a.rotate, b.rotate) && compare(a.scale, b.scale) && compare(a.translate, b.translate);
}

bool compare(Transform3 a, Transform3 b)
{
  return compare(a.rotate, b.rotate) && compare(a.scale, b.scale) && compare(a.translate, b.translate);
}

//------------------------------------------------------------------------------------------------------------------------------
// If( A != B ) an error is printed.
//------------------------------------------------------------------------------------------------------------------------------
#define COMPARE(A, B) \
  { \
     if(!compare( (A), (B) )) std::cerr << "FAILURE: " << __LINE__ << std::endl; \
  }

// test all methods in Vec2
void testVec2()
{
  // Vec2() : x(0), y(0) {}
  {
    Vec2 a;
    Vec2 b;
    b.x = 0;
    b.y = 0;
    COMPARE(a, b);
  }

  // Vec2(float s) : x(s), y(s) {}
  {
    Vec2 a(1.0f);
    Vec2 b;
    b.x = 1.0f;
    b.y = 1.0f;
    COMPARE(a, b);
  }

  // Vec2(float X, float Y) : x(X), y(Y) {}
  {
    Vec2 a(1.0f, 2.0f);
    Vec2 b;
    b.x = 1.0f;
    b.y = 2.0f;
    COMPARE(a, b);
  }

  // const Vec2& operator  = (Vec2 b);
  {
    Vec2 a(1.0f, 2.0f);
    Vec2 b;
    b = a;
    COMPARE(a, b);
  }

  // const Vec2& operator += (Vec2 b);
  {
    Vec2 a(1.0f, 2.0f);
    Vec2 b(2.0f, 4.0f);
    Vec2 c(3.0f, 6.0f);
    a += b;
    COMPARE(a, c);
  }

  // const Vec2& operator -= (Vec2 b);
  {
    Vec2 a(1.0f, 2.0f);
    Vec2 b(2.0f, 4.0f);
    Vec2 c(-1.0f, -2.0f);
    a -= b;
    COMPARE(a, c);
  }

  // const Vec2& operator *= (float b);
  {
    Vec2 a(1.0f, 2.0f);
    Vec2 b(2.0f, 4.0f);
    a *= 2.0f;
    COMPARE(a, b);
  }

  // const Vec2& operator /= (float b);
  {
    Vec2 a(1.0f, 2.0f);
    Vec2 b(2.0f, 4.0f);
    a /= 0.5f;
    COMPARE(a, b);
  }

  // float dot(Vec2 a, Vec2 b);
  {
    Vec2 a(1.0f, 2.0f);
    Vec2 b(2.0f, 4.0f);
    COMPARE(10.0f, dot(a, b));
  }

  // float length2(Vec2 a)
  {
    Vec2 a(1.0f, 2.0f);
    COMPARE(5.0f, length2(a));
  }

  // float length(Vec2 a)
  {
    Vec2 a(1.0f, 2.0f);
    COMPARE(sqrtf(5.0f), length(a));
  }

  // Vec2 normalize(Vec2 a);
  {
    Vec2 a(0.0f, 2.0f);
    Vec2 b(2.0f, 0.0f);
    Vec2 c(0.0f, 1.0f);
    Vec2 d(1.0f, 0.0f);
    COMPARE(c, normalize(a));
    COMPARE(d, normalize(b));
  }

  // Vec2 operator - (Vec2 a);
  {
    Vec2 a(1.0f, 2.0f);
    Vec2 b(-1.0f, -2.0f);
    COMPARE(-a, b);
  }

  // Vec2 operator + (Vec2 a, Vec2 b);
  {
    Vec2 a(1.0f, 2.0f);
    Vec2 b(2.0f, 4.0f);
    Vec2 c(3.0f, 6.0f);
    Vec2 d = a + b;
    COMPARE(c, d);
  }

  // Vec2 operator - (Vec2 a, Vec2 b);
  {
    Vec2 a(1.0f, 2.0f);
    Vec2 b(2.0f, 4.0f);
    Vec2 c(-1.0f, -2.0f);
    Vec2 d = a - b;
    COMPARE(c, d);
  }

  // Vec2 operator * (float b, Vec2 a);
  {
    Vec2 a(1.0f, 2.0f);
    Vec2 b(2.0f, 4.0f);
    Vec2 c = 2.0f * a;
    COMPARE(c, b);
  }

  // Vec2 operator * (Vec2 a, float b);
  {
    Vec2 a(1.0f, 2.0f);
    Vec2 b(2.0f, 4.0f);
    Vec2 c = a * 2.0f;
    COMPARE(c, b);
  }

  // Vec2 operator / (Vec2 a, float b);
  {
    Vec2 a(1.0f, 2.0f);
    Vec2 b(2.0f, 4.0f);
    Vec2 c = a / 0.5f;
    COMPARE(c, b);
  }
}

// test all methods in Vec3
void testVec3()
{
  // Vec3();
  {
    Vec3 a;
    Vec3 b;
    b.x = 0;
    b.y = 0;
    b.z = 0;
    COMPARE(a, b);
  }

  // Vec3(float s) ;
  {
    Vec3 a(1.0f);
    Vec3 b;
    b.x = 1.0f;
    b.y = 1.0f;
    b.z = 1.0f;
    COMPARE(a, b);
  }

  // Vec3(float X, float Y, float Z) 
  {
    Vec3 a(1.0f, 2.0f, 3.0f);
    Vec3 b;
    b.x = 1.0f;
    b.y = 2.0f;
    b.z = 3.0f;
    COMPARE(a, b);
  }

  // const Vec3& operator  = (Vec3 b);
  {
    Vec3 a(1.0f, 2.0f, 3.0f);
    Vec3 b;
    b = a;
    COMPARE(a, b);
  }

  // const Vec3& operator += (Vec3 b);
  {
    Vec3 a(1.0f, 2.0f, 3.0f);
    Vec3 b(2.0f, 4.0f, 6.0f);
    Vec3 c(3.0f, 6.0f, 9.0f);
    a += b;
    COMPARE(a, c);
  }

  // const Vec3& operator -= (Vec3 b);
  {
    Vec3 a(1.0f, 2.0f, 3.0f);
    Vec3 b(2.0f, 4.0f, 6.0f);
    Vec3 c(-1.0f, -2.0f, -3.0f);
    a -= b;
    COMPARE(a, c);
  }

  // const Vec3& operator *= (float b);
  {
    Vec3 a(1.0f, 2.0f, 3.0f);
    Vec3 b(2.0f, 4.0f, 6.0f);
    a *= 2.0f;
    COMPARE(a, b);
  }

  // const Vec3& operator /= (float b);
  {
    Vec3 a(1.0f, 2.0f, 3.0f);
    Vec3 b(2.0f, 4.0f, 6.0f);
    a /= 0.5f;
    COMPARE(a, b);
  }

  // float dot(Vec3 a, Vec3 b);
  {
    Vec3 a(1.0f, 2.0f, 3.0f);
    Vec3 b(2.0f, 4.0f, 6.0f);
    COMPARE(28.0f, dot(a, b));
  }

  // float length2(Vec3 a)
  {
    Vec3 a(1.0f, 2.0f, 3.0f);
    COMPARE(14.0f, length2(a));
  }

  // float length(Vec3 a)
  {
    Vec3 a(1.0f, 2.0f, 3.0f);
    COMPARE(sqrtf(14.0f), length(a));
  }

  // Vec3 normalize(Vec3 a);
  {
    Vec3 a(0.0f, 2.0f, 0.0f);
    Vec3 b(2.0f, 0.0f, 0.0f);
    Vec3 c(0.0f, 0.0f, 2.0f);
    Vec3 d(0.0f, 1.0f, 0.0f);
    Vec3 e(1.0f, 0.0f, 0.0f);
    Vec3 f(0.0f, 0.0f, 1.0f);
    COMPARE(d, normalize(a));
    COMPARE(e, normalize(b));
    COMPARE(f, normalize(c));
  }

  // Vec3 operator - (Vec3 a);
  {
    Vec3 a(1.0f, 2.0f, 3.0f);
    Vec3 b(-1.0f, -2.0f, -3.0f);
    COMPARE(-a, b);
  }

  // Vec3 operator + (Vec3 a, Vec3 b);
  {
    Vec3 a(1.0f, 2.0f, 3.0f);
    Vec3 b(2.0f, 4.0f, 6.0f);
    Vec3 c(3.0f, 6.0f, 9.0f);
    Vec3 d = a + b;
    COMPARE(c, d);
  }

  // Vec3 operator - (Vec3 a, Vec3 b);
  {
    Vec3 a(1.0f, 2.0f, 3.0f);
    Vec3 b(2.0f, 4.0f, 6.0f);
    Vec3 c(-1.0f, -2.0f, -3.0f);
    Vec3 d = a - b;
    COMPARE(c, d);
  }

  // Vec3 operator * (float b, Vec3 a);
  {
    Vec3 a(1.0f, 2.0f, 3.0f);
    Vec3 b(2.0f, 4.0f, 6.0f);
    Vec3 c = 2.0f * a;
    COMPARE(c, b);
  }

  // Vec3 operator * (Vec3 a, float b);
  {
    Vec3 a(1.0f, 2.0f, 3.0f);
    Vec3 b(2.0f, 4.0f, 6.0f);
    Vec3 c = a * 2.0f;
    COMPARE(c, b);
  }

  // Vec3 operator / (Vec3 a, float b);
  {
    Vec3 a(1.0f, 2.0f, 3.0f);
    Vec3 b(2.0f, 4.0f, 6.0f);
    Vec3 c = a / 0.5f;
    COMPARE(c, b);
  }
}

// test all methods in Matrix2
void testMatrix2()
{
  // Matrix2()
  {
    Matrix2 a;
    Matrix2 b;
    b.x = Vec2(1.0f, 0.0f);
    b.y = Vec2(0.0f, 1.0f);
    b.w = Vec2(0.0f, 0.0f);
    COMPARE(a, b);
  }

  // Matrix2()
  {
    Matrix2 a(1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    Matrix2 b;
    b.x = Vec2(1.0f, 0.0f);
    b.y = Vec2(0.0f, 1.0f);
    b.w = Vec2(0.0f, 0.0f);
    COMPARE(a, b);
  }

  // Matrix2()
  {
    Matrix2 a(Vec2(1.0f, 0.0f), Vec2(0.0f, 1.0f), Vec2(0.0f, 0.0f));
    Matrix2 b;
    b.x = Vec2(1.0f, 0.0f);
    b.y = Vec2(0.0f, 1.0f);
    b.w = Vec2(0.0f, 0.0f);
    COMPARE(a, b);
  }
  
  // Vec2 rotate(const Matrix2& m, Vec2 v);
  {
    Matrix2 a(Vec2(0.0f, 1.0f), Vec2(-1.0f, 0.0f), Vec2(2.0f, 0.5f));
    Vec2 b(2.0f, 1.0f);
    Vec2 c(-1.0f, 2.0f);
    Vec2 d = rotate(a, b);
    COMPARE(c, d);
  }

  // Vec2 transform(const Matrix2& m, Vec2 v);
  {
    Matrix2 a(Vec2(0.0f, 1.0f), Vec2(-1.0f, 0.0f), Vec2(2.0f, 0.5f));
    Vec2 b(2.0f, 1.0f);
    Vec2 c(1.0f, 2.5f);
    Vec2 d = transform(a, b);
    COMPARE(c, d);
  }

  // Vec2 inverseRotate(const Matrix2& m, Vec2 v);
  {
    Matrix2 a(Vec2(0.0f, 1.0f), Vec2(-1.0f, 0.0f), Vec2(2.0f, 0.5f));
    Vec2 b(-1.0f, 2.0f);
    Vec2 c(2.0f, 1.0f);
    Vec2 d = inverseRotate(a, b);
    COMPARE(c, d);
  }

  // Vec2 inverseTransform(const Matrix2& m, Vec2 v);
  {
    Matrix2 a(Vec2(0.0f, 1.0f), Vec2(-1.0f, 0.0f), Vec2(2.0f, 0.5f));
    Vec2 b(1.0f, 2.5f);
    Vec2 c(2.0f, 1.0f);
    Vec2 d = inverseTransform(a, b);
    COMPARE(c, d);
  }
}

// test all methods in Matrix3
void testMatrix3()
{
  // Matrix3()
  {
    Matrix3 a;
    Matrix3 b;
    b.x = Vec3(1.0f, 0.0f, 0.0f);
    b.y = Vec3(0.0f, 1.0f, 0.0f);
    b.z = Vec3(0.0f, 0.0f, 1.0f);
    b.w = Vec3(0.0f, 0.0f, 0.0f);
    COMPARE(a, b);
  }

  // Matrix3()
  {
    Matrix3 a(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
    Matrix3 b;
    b.x = Vec3(1.0f, 0.0f, 0.0f);
    b.y = Vec3(0.0f, 1.0f, 0.0f);
    b.z = Vec3(0.0f, 0.0f, 1.0f);
    b.w = Vec3(0.0f, 0.0f, 0.0f);
    COMPARE(a, b);
  }

  // Matrix3()
  {
    Matrix3 a(Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f), Vec3(0.0f, 0.0f, 0.0f));
    Matrix3 b;
    b.x = Vec3(1.0f, 0.0f, 0.0f);
    b.y = Vec3(0.0f, 1.0f, 0.0f);
    b.z = Vec3(0.0f, 0.0f, 1.0f);
    b.w = Vec3(0.0f, 0.0f, 0.0f);
    COMPARE(a, b);
  }
  
  // Vec3 rotate(const Matrix3& m, Vec3 v);
  {
    Matrix3 a(Vec3(0.0f, 2.0f, 0.0f), 
              Vec3(-1.5f, 0.0f, 0.0f), 
              Vec3(0.0f, 0.0f, 1.0f), 
              Vec3(2.0f, 1.5f, 3.3f));
    Vec3 b(1.0f, 2.0f, 3.0f);
    Vec3 c = Vec3(0.0f, 2.0f, 0.0f) * 1.0f + Vec3(-1.5f, 0.0f, 0.0f) * 2.0f + Vec3(0.0f, 0.0f, 1.0f) * 3.0f;
    Vec3 d = rotate(a, b);
    COMPARE(d, c);
  }

  // Vec3 transform(const Matrix3& m, Vec3 v);
  {
    Matrix3 a(Vec3(0.0f, 2.0f, 0.0f), 
              Vec3(-1.5f, 0.0f, 0.0f), 
              Vec3(0.0f, 0.0f, 1.0f), 
              Vec3(2.0f, 1.5f, 3.3f));
    Vec3 b(1.0f, 2.0f, 3.0f);
    Vec3 c = Vec3(0.0f, 2.0f, 0.0f) * 1.0f + Vec3(-1.5f, 0.0f, 0.0f) * 2.0f + Vec3(0.0f, 0.0f, 1.0f) * 3.0f + Vec3(2.0f, 1.5f, 3.3f);
    Vec3 d = transform(a, b);
    COMPARE(d, c);
  }

  // Vec3 inverseRotate(const Matrix3& m, Vec3 v);
  {
    Matrix3 a(Vec3(0.0f, 2.0f, 0.0f), 
              Vec3(-1.5f, 0.0f, 0.0f), 
              Vec3(0.0f, 0.0f, 1.0f), 
              Vec3(2.0f, 1.5f, 3.3f));
    Vec3 b = Vec3(0.0f, 2.0f, 0.0f) * 1.0f + Vec3(-1.5f, 0.0f, 0.0f) * 2.0f + Vec3(0.0f, 0.0f, 1.0f) * 3.0f;
    Vec3 c(1.0f, 2.0f, 3.0f);
    Vec3 d = inverseRotate(a, b);
    COMPARE(d, c);
  }

  // Vec3 inverseTransform(const Matrix3& m, Vec3 v);
  {
    Matrix3 a(Vec3(0.0f, 2.0f, 0.0f), 
              Vec3(-1.5f, 0.0f, 0.0f), 
              Vec3(0.0f, 0.0f, 1.0f), 
              Vec3(2.0f, 1.5f, 3.3f));
    Vec3 b = Vec3(0.0f, 2.0f, 0.0f) * 1.0f + Vec3(-1.5f, 0.0f, 0.0f) * 2.0f + Vec3(0.0f, 0.0f, 1.0f) * 3.0f + Vec3(2.0f, 1.5f, 3.3f);
    Vec3 c(1.0f, 2.0f, 3.0f);
    Vec3 d = inverseTransform(a, b);
    COMPARE(d, c);
  }
  
  //void setRotateX(float rotate);
  {
    Matrix3 a;
    a.setRotateX(1.0f);
    Matrix3 b(1, 0, 0,   0, 0.540302, 0.841471, 0, -0.841471, 0.540302, 0, 0, 0);
    COMPARE(a, b);
  }
  
  //void setRotateY(float rotate);
  {
    Matrix3 a;
    a.setRotateY(1.0f);
    Matrix3 b(0.540302f, 0.f, -0.841471f, 0.0f, 1.0f, 0.0f, 0.841471f, 0.f, 0.540302f, 0, 0, 0);
    COMPARE(a, b);
  }
  
  //void setRotateZ(float rotate);
  {
    Matrix3 a;
    a.setRotateZ(1.0f);
    Matrix3 b(0.540302f, 0.841471f, 0.0f, -0.841471f, 0.540302f, 0,  0.0f, 0.0f, 1.0f, 0, 0, 0);
    COMPARE(a, b);
  }
}

// test all methods in Transform2
void testTransform2()
{

  Transform2 t;
  t.rotate = 1.0f;
  t.scale.x = 2.1f;
  t.scale.y = 1.4f;
  t.translate.x = 3.1f;
  t.translate.y = 2.6f;

  float ca = cos(t.rotate);
  float sa = sin(t.rotate);
  Matrix2 mtest;
  mtest.x.x = ca * t.scale.x;
  mtest.x.y = sa * t.scale.x;
  mtest.y.x =-sa * t.scale.y;
  mtest.y.y = ca * t.scale.y;
  mtest.w.x = 3.1f;
  mtest.w.y = 2.6f;

  // operator Matrix2 () const 
  {
    Matrix2 m;
    m = t;
    COMPARE(mtest, m);
  }
  
  // Transform2(const Matrix2& m) 
  {
    Transform2 tt;
    tt = mtest;
    COMPARE(tt, t);
  }

  {
    Transform2 t1;
    t1.rotate = 0;
    t1.scale.x = 1.0f;
    t1.scale.y = 1.0f;
    t1.translate.x = 0.0f;
    t1.translate.y = 0.0f;
    Transform2 t2;
    COMPARE(t1, t2);
  }

  {
    Transform2 t1(1.0f, Vec2(2.1f, 1.4f), Vec2(3.1f, 2.6f));
    COMPARE(t1, t);
  }

  /// translates the transform relative to it's local coordinate frame (effectively strafing!)
  {
    Vec2 offset(2.0f, 3.0f);
    Transform2 t1 = t;
    t1.moveLocal(offset);
    offset = rotate(mtest, offset);
    COMPARE(mtest.w + offset, t1.translate);
  }

  /// translates the transform relative to the world coordinate frame
  {
    Vec2 offset(2.0f, 3.0f);
    Transform2 t1 = t;
    t1.moveGlobal(offset);
    COMPARE(mtest.w + offset, t1.translate);
  }
}

// test all methods in Transform3
void testTransform3()
{

  Transform3 t;
  t.rotate.x = 1.0f;
  t.rotate.y = 2.0f;
  t.rotate.z = 3.0f;
  t.scale.x = 2.1f;
  t.scale.y = 1.4f;
  t.scale.z = 0.8f;
  t.translate.x = 3.1f;
  t.translate.y = 2.6f;
  t.translate.z = 1.3f;

  // This matrix result comes from maya when transforms are set to XYZ rotation order. 
  Matrix3 mtest(0.865163f, -0.123326f, -1.909525f, -1.167233f, -0.597685f, -0.490246f, -0.294104f, 0.721905f, -0.179876f, 3.1f, 2.6f, 1.3f);

  // operator Matrix3 () const 
  {
    // so this will now match maya! Huzzah!
    Matrix3 m;
    m = t;
    COMPARE(mtest, m);
  }
  
  {
    Transform3 t1;
    t1.rotate = Vec3(0, 0, 0);
    t1.scale.x = 1.0f;
    t1.scale.y = 1.0f;
    t1.scale.z = 1.0f;
    t1.translate.x = 0.0f;
    t1.translate.y = 0.0f;
    t1.translate.z = 0.0f;
    Transform3 t2;
    COMPARE(t1, t2);
  }

  {
    Transform3 t1(Vec3(1.0f, 2.0f, 3.0f), Vec3(2.1f, 1.4f, 0.8f), Vec3(3.1f, 2.6f, 1.3f));
    COMPARE(t1, t);
  }
}

//------------------------------------------------------------------------------------------------------------------------------------
/// main  \o/
//------------------------------------------------------------------------------------------------------------------------------------
int main()
{
  // just run all of the tests
  testVec2();
  testVec3();
  testMatrix2();
  testMatrix3();
  testTransform2();
  testTransform3();
  return 0;
}
