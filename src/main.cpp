#include <raylib.h>
#include <PVector3.hpp>
#include <Planet.hpp>
#include <Window.hpp>
#include <PCamera.hpp>
#include <iostream>
using namespace VMath;


int main(void)
{
  // initialize
  Window window;
  Ray ray;
  PCamera* pcamera = PCamera::instance();
  Camera camera = *(pcamera->getCamera());
  
  // planets
  Planet earth { "res/earth/earth.obj", "res/earth/earth_albedo.png", (Vector3) {0.0, 0.0, 0.0}, 1.0f};
  
  SetTargetFPS(60);               // target 60 fps

  // Main game loop
  while (!WindowShouldClose())    // Detect window close button or ESC key
    {

      // Update
      pcamera->Update();
      
      ray = GetMouseRay(GetMousePosition(), camera);

      earth.CheckPointer(ray); earth.Update();
	  
      if (earth.getClicked()) // zoom towards Earth
	{
	  pcamera->SetTarget(&earth);
	}
	  
      // Draw
      BeginDrawing();
      BeginMode3D(camera);
	  
      ClearBackground(BLACK);
      earth.Draw();
      
      
      EndMode3D();
      EndDrawing();
      
    }

  return 0;
}

