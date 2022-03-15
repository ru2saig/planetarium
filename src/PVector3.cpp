#include <PVector3.hpp>
#include <cmath>

using namespace VMath;

PVector3::PVector3()
{
  vec3.x = 0;
  vec3.y = 0;
  vec3.z = 0;
}

PVector3::PVector3(double a)
{
  vec3.x = a;
  vec3.y = a;
  vec3.z = a;
}

PVector3::PVector3(double x, double y, double z)
{
  vec3.x = x;
  vec3.y = y;
  vec3.z = z;
}

PVector3 PVector3::operator+(PVector3 &b)
{
  double x = this->vec3.x + b.vec3.x;
  double y = this->vec3.y + b.vec3.y;
  double z = this->vec3.z + b.vec3.z;

  return PVector3{x, y, z};
}

PVector3 PVector3::operator-(PVector3 &b)
{
  double x = this->vec3.x - b.vec3.x;
  double y = this->vec3.y - b.vec3.y;
  double z = this->vec3.z - b.vec3.z;

  return PVector3{x, y, z};
}

double PVector3::operator*(PVector3 &b)
{
  return (this->vec3.x*b.vec3.x + this->vec3.y*b.vec3.y + this->vec3.z*b.vec3.z);
}

PVector3 cross(PVector3 &a, PVector3 &b) {

  double x = a.vec3.y*b.vec3.z + a.vec3.z*b.vec3.y;
  double y = a.vec3.z*b.vec3.x + a.vec3.x*b.vec3.z;
  double z = a.vec3.x*b.vec3.y + a.vec3.y*b.vec3.x;

  return PVector3{x, y, z};
}

double PVector3::mag()
{
  return sqrt(this->vec3.x*this->vec3.x + this->vec3.y*this->vec3.y + this->vec3.z*this->vec3.z);
}

PVector3 PVector3::normalize()
{
  double m = mag();
  double x = this->vec3.x/m;
  double y = this->vec3.y/m;
  double z = this->vec3.z/m;

  return PVector3{x, y, z};
}

