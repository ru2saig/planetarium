#include <Orbit.hpp>
#include <raylib.h>
#include <cmath>
#include <iostream>

constexpr float rad = 2.0f * PI;

Orbit::Orbit()
  : radius { 0.0f }, period { 0.0f }
{}

// TODO: why isn't period in seconds? what is wrong?
Orbit::Orbit(float radius, float period,
             Vector3 centre = Vector3{0.0f, 0.0f, 0.0f})
  : radius{radius}, centre{centre}, progress { 0.0f }
{
  this->period = period/rad;
}

void Orbit::Draw()
{
  DrawCircle3D(centre, radius, Vector3 { 0.0f, 0.0f, 0.0f }, 0.0f, PINK);
}

void Orbit::Update()
{
  if(period < 0.0001) // so no divide by zero shenanigans occur
    period = 0.0001;
  float freq = 1.0f/period;
  progress += GetFrameTime() * freq;
  progress = fmod(progress, rad);
}

Vector3 Orbit::Evaluate()
{
  float x = radius*std::cos(this->progress);
  float y = radius*std::sin(this->progress);

  return Vector3 { x, y, 0.0f};
}
