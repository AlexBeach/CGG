#pragma once
#include "cgg/Vec3.h"
#include "cgg/Matrix2.h"

/// declares a type called 'Matrix3' that represents a 3D transform matrix
struct Matrix3
{
  Vec3 x; ///< the X axis direction
  Vec3 y; ///< the Y axis direction
  Vec3 z; ///< the Y axis direction
  Vec3 w; ///< the position of the transform

  /// constructor functions (initialises to the Identity matrix)
  Matrix3() 
    : x(1.0f, 0.0f, 0.0f), 
      y(0.0f, 1.0f, 0.0f), 
      z(0.0f, 0.0f, 1.0f), 
      w(0.0f, 0.0f, 0.0f) {}

  /// Constructs a 3D matrix from a 2D one
  Matrix3(const Matrix2& m) 
    : x(m.x), 
      y(m.y), 
      z(0.0f, 0.0f, 1.0f), 
      w(m.w) {}
  
  /// initialises the matrix from 12 floats 
  Matrix3(float xx, float xy, float xz, 
          float yx, float yy, float yz,
          float zx, float zy, float zz,
          float wx, float wy, float wz)
     : x(xx, xy, xz), y(yx, yy, yz), z(zx, zy, zz), w(wx, wy, wz)
  {}
  
  /// initialises the matrix from 4x3D vectors
  Matrix3(Vec3 X, 
          Vec3 Y,
          Vec3 Z,
          Vec3 W) : x(X), y(Y), z(Z), w(W)
  {}
  
  /// sets this matrix to a X rotation matrix
  void setRotateX(float rotate)
  {
    float ca = std::cosf(rotate);
    float sa = std::sinf(rotate);
    x = Vec3(1.0f, 0.0f, 0.0f);
    y = Vec3(0.0f, ca, sa);
    z = Vec3(0.0f,-sa, ca);
    w = Vec3();
  }
  
  /// sets this matrix to a Y rotation matrix
  void setRotateY(float rotate)
  {
    float ca = std::cosf(rotate);
    float sa = std::sinf(rotate);
    x = Vec3(ca, 0.0f, -sa);
    y = Vec3(0.0f, 1.0f, 0.0f);
    z = Vec3(sa, 0.0f, ca);
    w = Vec3();
  }
  
  /// sets this matrix to a Z rotation matrix
  void setRotateZ(float rotate)
  {
    float ca = std::cosf(rotate);
    float sa = std::sinf(rotate);
    x = Vec3(ca, sa, 0.0f);
    y = Vec3(-sa, ca, 0.0f);
    z = Vec3(0.0f, 0.0f, 1.0f);
    w = Vec3();
  }
  
  friend Vec3 rotate(const Matrix3& m, Vec3 v);
  friend Vec3 tranform(const Matrix3& m, Vec3 v);

  /// translates the transform relative to it's local coordinate frame (effectively strafing!)
  void moveLocal(Vec3 offset)
    {
      offset = rotate(*this, offset);
      w += offset;
    }

  /// translates the transform relative to the world coordinate frame
  void moveGlobal(Vec3 offset)
    {
      w += offset;
    }
};

/// rotate the 3D vector v by the matrix m
inline Vec3 rotate(const Matrix3& m, Vec3 v)
{
  Vec3 r = m.x * v.x;
  r += m.y * v.y;
  r += m.z * v.z;
  return r;
}

/// transfrms the 3D point p by the matrix m
inline Vec3 transform(const Matrix3& m, Vec3 p)
{
  return rotate(m, p) + m.w;
}

/// rotate the 3D vector v by the inverse of matrix m
inline Vec3 inverseRotate(const Matrix3& m, Vec3 v)
{
  Vec3 r;
  r.x = dot(v, m.x) / dot(m.x, m.x);
  r.y = dot(v, m.y) / dot(m.y, m.y);
  r.z = dot(v, m.z) / dot(m.z, m.z);
  return r;
}

/// transfrms the 3D point p by the inverse of matrix m
inline Vec3 inverseTransform(const Matrix3& m, Vec3 p)
{
  return inverseRotate(m, p - m.w);
}

inline Matrix3 operator * (const Matrix3& child, const Matrix3& parent)
{
  Matrix3 r;
  r.x = rotate(parent, child.x);
  r.y = rotate(parent, child.y);
  r.z = rotate(parent, child.z);
  r.w = transform(parent, child.w);
  return r;
}
