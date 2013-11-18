#pragma once
#include "cgg/Vec2.h"

// declares a type called 'Matrix2' that represents a 2D transform matrix
struct Matrix2
{
  Vec2 x; ///< the X axis direction
  Vec2 y; ///< the Y axis direction
  Vec2 w; ///< the position of the transform

  // constructor functions (initialises to the Identity matrix)
  Matrix2() : x(1.0f, 0.0f), y(0.0f, 1.0f), w(0.0f, 0.0f) {}
  
  // initialises the matrix from 6 floats 
  Matrix2(float xx, float xy, 
          float yx, float yy,
          float wx, float wy) : x(xx, xy), y(yx, yy), w(wx, wy)
  {}
  
  // initialises the matrix from 3x2D vectors
  Matrix2(Vec2 X, 
          Vec2 Y,
          Vec2 W) : x(X), y(Y), w(W)
  {}
  
  friend Vec2 rotate(const Matrix2& m, Vec2 v);
  friend Vec2 tranform(const Matrix2& m, Vec2 v);

  /// translates the transform relative to it's local coordinate frame (effectively strafing!)
  void moveLocal(Vec2 offset)
    {
      offset = rotate(*this, offset);
      w += offset;
    }

  /// translates the transform relative to the world coordinate frame
  void moveGlobal(Vec2 offset)
    {
      w += offset;
    }
};

// rotate the 2D vector v by the matrix m
inline Vec2 rotate(const Matrix2& m, Vec2 v)
{
  Vec2 r = m.x * v.x;
  r += m.y * v.y;
  return r;
}

// transfrms the 2D point p by the matrix m
inline Vec2 transform(const Matrix2& m, Vec2 p)
{
  return rotate(m, p) + m.w;
}

// rotate the 2D vector v by the inverse of matrix m
inline Vec2 inverseRotate(const Matrix2& m, Vec2 v)
{
  Vec2 r;
  r.x = dot(v, m.x) / dot(m.x, m.x);
  r.y = dot(v, m.y) / dot(m.y, m.y);
  return r;
}

// transfrms the 2D point p by the inverse of matrix m
inline Vec2 inverseTransform(const Matrix2& m, Vec2 p)
{
  return inverseRotate(m, p - m.w);
}
