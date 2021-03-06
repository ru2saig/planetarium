#pragma once
#include <raylib.h>
#include <CelestialBody.hpp>
#include <Utility.hpp>

class Sun : public CelestialBody
{
public:
  Model model;
  Texture2D texture;
  
  Sun(string, string);
  ~Sun();
  
  void Draw() override;
  void Update() override;
  void DisplayInfo() override;
  void CheckPointer(Ray);
  
  bool getClicked() { return clicked; }
  float getRadius() { return radius; }
  
private:
  char* sunInfo;
  RayCollision sunEntered; // when pointer enters box
};

