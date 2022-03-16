#pragma once
#include <raylib.h>

namespace VMath{

  Vector3 operator+(Vector3 a, Vector3 b);
  Vector3 operator-(Vector3 a, Vector3 b);
  float  operator*(Vector3 a, Vector3 b);
  Vector3 operator*(float a, Vector3 b);
  Vector3 operator*(Vector3 a, float b);
  Vector3 cross(Vector3 a, Vector3 b);
  Vector3 normalize(Vector3 a);
  float mag(Vector3 a);

}
