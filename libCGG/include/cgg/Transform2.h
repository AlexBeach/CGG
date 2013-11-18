#pragma once
#include "cgg/Matrix2.h"

/// a class that represents a 2D transformation. Can be coverted to/from a matrix2
struct Transform2
{
  float rotate;   ///< the rotation angle
  Vec2 scale;     ///< the scaling in the X ad Y axes
  Vec2 translate; ///< the translation 
  
  /// sets to default values
  Transform2() 
    : rotate(0), scale(1.0f, 1.0f), translate(0.0f, 0.0f) {}
  
  /// initialises to the specified transform values
  Transform2(float r, Vec2 s, Vec2 t) 
    : rotate(r), scale(s), translate(t) {}
  
  /// initialises from a matrix
  Transform2(const Matrix2& m) 
    : rotate(std::atan2f(m.x.y, m.x.x)), scale(length(m.x), length(m.y)), translate(m.w)
    {
      // generate a hacky new Y axis.
      Vec2 tempy(-m.x.y, m.x.x);
      // if that vector is facing in the opposite direction to the one in the matrix, we've got a negative scale value :(
      if(dot(m.y, tempy) < 0)
      {
        // so negate the 'y' scale value
        scale.y = -scale.y;
      }
    }

  /// translates the transform relative to it's local coordinate frame (effectively strafing!)
  void moveLocal(Vec2 offset)
    {
      float ca = std::cosf(rotate);
      float sa = std::sinf(rotate);
      Vec2 X( ca * offset.x * scale.x, sa * offset.x * scale.x);
      Vec2 Y(-sa * offset.y * scale.y, ca * offset.y * scale.y);
      translate += (X + Y);
    }

  /// translates the transform relative to the world coordinate frame
  void moveGlobal(Vec2 offset)
    {
      translate += offset;
    }

  /// automatically converts from a 2D transform to a 2D matrix
  inline operator Matrix2 () const 
    {
      float ca = std::cosf(rotate);
      float sa = std::sinf(rotate);
      Vec2 x( ca * scale.x, sa * scale.x);
      Vec2 y(-sa * scale.y, ca * scale.y);
      return Matrix2(x, y, translate);
    }
};
