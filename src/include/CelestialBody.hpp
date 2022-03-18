#pragma once
#include <raylib.h>
typedef const char* string;

class CelestialBody {
public:
  virtual void Draw() = 0; 
  virtual void Update() = 0;
  virtual void DisplayInfo() = 0;
  virtual ~CelestialBody () {}

  Vector3 getPosition() { return pos; }
  float getRadius() { return radius; }
protected:
  Vector3 pos;
  float radius;
};
