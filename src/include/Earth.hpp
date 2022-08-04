#include <Planet.hpp>
#include <iostream>
#include <raylib.h>
#include <rlgl.h>

class Earth : public Planet                  
{
public:
  Earth(Camera* camera);
  ~Earth() = default;
  
  void Draw();
  void Update();

private:
  Camera* camera;  
};                  
