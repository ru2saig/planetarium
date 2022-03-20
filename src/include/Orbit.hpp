#pragma once
#include <raylib.h>

// TODO: make the orbit elliptical
// right now the orbit is modelled as a circle
class Orbit
{
public:
  Orbit(float, float, Vector3);
  Orbit();
  
  void Draw();
  void Update();
  Vector3 Evaluate(); // takes a progess (0.0 to 1.0) and returns position in the orbit

private:
  float progress;
  float period;
  float radius;
  Vector3 centre; // location of the Sun
};   
