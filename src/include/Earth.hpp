#include <Planet.hpp>
#include <raylib.h>
#include <rlgl.h>

class Earth : public Planet                  
{
public:
  Earth(Camera* camera);
  ~Earth();

  void Draw();
  void Update();

private:
  Camera* camera;
  Shader shader;
  
};                  
