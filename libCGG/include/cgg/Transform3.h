#pragma once
#include "cgg/Matrix3.h"

struct Transform3
{
  Vec3 rotate;   ///< the rotation angle
  Vec3 scale;     ///< the scaling in the X ad Y axes
  Vec3 translate; ///< the translation 
  
  /// sets to default values
  Transform3() 
    : rotate(0), scale(1.0f, 1.0f), translate(0.0f, 0.0f) {}
  
  /// initialises to the specified transform values
  Transform3(Vec3 r, Vec3 s, Vec3 t) 
    : rotate(r), scale(s), translate(t) {}
  
  /// automatically converts from a 2D transform to a 2D matrix
  inline operator Matrix3 () const 
    {
      Matrix3 rx;
      Matrix3 ry;
      Matrix3 rz;
      rx.setRotateX(rotate.x);
      ry.setRotateY(rotate.y);
      rz.setRotateZ(rotate.z);
      Matrix3 r;
      r = rx * ry * rz;
      r.x *= scale.x;
      r.y *= scale.y;
      r.z *= scale.z;
      r.w = translate;
      return r;
    }
};
