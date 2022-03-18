#pragma once
#include <raylib.h>

class CelestialBody {
public:
  virtual void Draw() = 0; 
  virtual void Update() = 0;
  virtual void DisplayInfo() = 0;
  virtual ~CelestialBody () {}

  Vector3 getPosition() { return pos; }
  float getRadius() { return radius; }
  bool getClicked() { return clicked; }
  
  void clickedTrue() { clicked = true; }
  void clickedFalse() { clicked = false;}
protected:
  bool clicked;
  Vector3 pos;
  float radius;
};
