#include <PVector3.hpp>
#include <raylib.h>
#include <cmath>


Vector3 VMath::operator+(Vector3 a, Vector3 b)
{
  return Vector3{ a.x+b.x, a.y+b.y, a.z+b.z};
}

Vector3 VMath::operator-(Vector3 a, Vector3 b)
{
  return Vector3{ a.x-b.x, a.y-b.y, a.z-b.z};
}

float  VMath::operator*(Vector3 a, Vector3 b)
{
  return a.x*b.x + a.y*b.y + a.z*b.z;
}

Vector3 VMath::operator*(float a, Vector3 b)
{
  return Vector3 { a*b.x, a*b.y, a*b.z};
}

Vector3 VMath::operator*(Vector3 b, float a)
{
  return Vector3 { a*b.x, a*b.y, a*b.z};
}

Vector3 VMath::cross(Vector3 a, Vector3 b)
{
  return Vector3{ a.y*b.z + a.z*b.y , a.z*b.x + a.x*b.z , a.x*b.y + a.y*b.x};
}

float VMath::mag(Vector3 a)
{
  return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}
Vector3 VMath::normalize(Vector3 a)
{
  float m = mag(a);
  float x = x/m;
  float y = y/m;
  float z = z/m;

  return Vector3{x, y, z};
}
