#pragma once
#include <raylib.h>
typedef const char* string;

class Planet
{
public:
  Model model;
  Texture2D texture;

  Planet(string, string, Vector3, float);
  ~Planet();
  
  void Draw();
  void Update();
  void DisplayInfo();
  bool IsClicked();
  Vector3 getPosition() { return pos; };
  
private:
  float scale;
  string info;
  Vector3 pos;
}; 
