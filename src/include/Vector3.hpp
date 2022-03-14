#pragma once

namespace VMath{
  
  struct Vector3
  {
    double x;
    double y;
    double z;
    
    Vector3(); // default, null/zero vector
    Vector3(double a);
    Vector3(double x, double y, double z);

    // vector operations
    Vector3 operator+(Vector3&);
    Vector3 operator-(Vector3&);
    double  operator*(Vector3&);

    friend Vector3 cross(Vector3&, Vector3&);
    Vector3 normalize();
    double mag();   
  };

  Vector3 cross(Vector3&, Vector3&);
}
