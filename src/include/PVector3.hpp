#pragma once
#include <raylib.h>

namespace VMath{
  
  struct PVector3
  {
    Vector3 vec3;
    
    PVector3(); // default, null/zero vector
    PVector3(double a);
    PVector3(double x, double y, double z);

    // vector operations
    PVector3 operator+(PVector3&);
    PVector3 operator-(PVector3&);
    double  operator*(PVector3&);
    PVector3 operator*(double);

    friend PVector3 cross(PVector3&, PVector3&);
    PVector3 normalize();
    double mag();
    Vector3 vector3() { return vec3; }
  };

  PVector3 cross(PVector3&, PVector3&);
}
