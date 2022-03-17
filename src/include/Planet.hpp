#pragma once
#include <raylib.h>
#include <CelestialBody.hpp>
typedef const char* string;
#define FLT_MAX     340282346638528859811704183484516925440.0f     // Maximum value of a float, from bit pattern 01111111011111111111111111111111

class Planet : CelestialBody
{
public:
  Model model;
  Texture2D texture;
  
  Planet(string, string, Vector3, float);
  ~Planet();
  
  void Draw() override;
  void Update() override;
  void DisplayInfo() override;
  void CheckPointer(Ray);
  Vector3 getPosition() { return pos; }
  
private:
  float scale;
  string info;
  Vector3 pos;
  BoundingBox box;
  RayCollision boundingBoxEntered; // when the bounding box is entered
  RayCollision planetClicked; // when the mesh is clicked
}; 
