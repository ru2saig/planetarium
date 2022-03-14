#include <Vector3.hpp>
#include <cmath>

using namespace VMath;

Vector3::Vector3() : x{0}, y{0}, z{0} {}
Vector3::Vector3(double a) : x{a}, y{a}, z{a} {}
Vector3::Vector3(double x, double y, double z):x{x}, y{y}, z{z} {}

Vector3 Vector3::operator+(Vector3 &b)
{
  double x = this->x + b.x;
  double y = this->y + b.y;
  double z = this->z + b.z;

  return Vector3{x, y, z};
}

Vector3 Vector3::operator-(Vector3 &b)
{
  double x = this->x - b.x;
  double y = this->y - b.y;
  double z = this->z - b.z;

  return Vector3{x, y, z};
}

double Vector3::operator*(Vector3 &b)
{
  return (this->x*b.x + this->y*b.y + this->z*b.z);
}

Vector3 cross(Vector3 &a, Vector3 &b) {

  double x = a.y*b.z + a.z*b.y;
  double y = a.z*b.x + a.x*b.z;
  double z = a.x*b.y + a.y*b.x;

  return Vector3{x, y, z};
}

double Vector3::mag()
{
  return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
}

Vector3 Vector3::normalize()
{
  double m = mag();
  double x = this->x/m;
  double y = this->y/m;
  double z = this->z/m;

  return Vector3{x, y, z};
}

