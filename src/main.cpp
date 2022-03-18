#include <raylib.h>
#include <PVector3.hpp>
#include <Planet.hpp>
#include <Window.hpp>
#include <iostream>

using namespace VMath;


int main(void)
{
  // Initialization
  Window window;


  Camera camera = { 0 };
  camera.position = (Vector3){ 100.0f, 100.0f, 100.0f }; // Camera position
  camera.target = (Vector3){ 0.0f, 10.0f, 0.0f };     // Camera looking at point
  camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;                                // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type
  

  
  // initialize the planets
  Planet earth { "res/earth/earth.obj", "res/earth/earth_albedo.png", (Vector3) {0.0, 0.0, 0.0}, 1.0f};

  SetCameraMode(camera, CAMERA_CUSTOM);
  SetTargetFPS(60);               // target 60 fps

  Ray ray;
  // Main game loop
  while (!WindowShouldClose())    // Detect window close button or ESC key
    {

      // Update
      // TODO: add a custom update function, as camera is in CAMERA_CUSTOM mode
      UpdateCamera(&camera);

      ray = GetMouseRay(GetMousePosition(), camera);

      earth.CheckPointer(ray);
      earth.Update();

      // if(earth.getClicked()) // zoom towards Earth
      // 	{
      // 	  // TODO: interpolate towards this
      // 	  camera.target = earth.getPosition();

      // 	  // TODO: interpolate towards this as well
      // 	  // TODO: Make the zoom a little better, perhaps make it something like the follows:
      // 	  camera.position = earth.getPosition() + (Vector3) {20.0, 20.0, 20.0};
      // 	}
      
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

