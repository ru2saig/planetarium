#pragma once
#include <raylib.h>
typedef const char* string;
#define FLT_MAX     340282346638528859811704183484516925440.0f     // Maximum value of a float, from bit pattern 01111111011111111111111111111111


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
