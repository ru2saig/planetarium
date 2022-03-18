#include <raylib.h>
#include <PVector3.hpp>
#include <Planet.hpp>
#include <Window.hpp>
#include <CameraManager.hpp>
#include <iostream>
using namespace VMath;

int main(void)
{
  // initialize
  Window window;
  Ray ray;

  CameraManager cm = CameraManager::instance();
  
  // planets
  Planet earth { "res/earth/earth.obj", "res/earth/earth_albedo.png", (Vector3) {0.0, 0.0, 0.0}, 1.0f};

  
  SetTargetFPS(60);               // target 60 fps

  // Main game loop
  while (!WindowShouldClose())    // Detect window close button or ESC key
    {

      // Update
      cm.Update();
      
      ray = GetMouseRay(GetMousePosition(), cm.getCamera());

      earth.CheckPointer(ray);
      earth.Update();
      
      if (earth.getClicked()) // zoom towards Earth
	{
	  cm.setTarget(&earth);
	}

      if (IsKeyPressed(KEY_Q))
	{
	  cm.unsetTarget();
	}
      
      // Draw
      BeginDrawing();
      BeginMode3D(cm.getCamera());
       
      ClearBackground(BLACK);
      earth.Draw();
      
      
      EndMode3D();
      EndDrawing();
      
    }

  return 0;
}

