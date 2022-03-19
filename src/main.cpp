#include <raylib.h>
#include <PVector3.hpp>
#include <Planet.hpp>
#include <Window.hpp>
#include <CameraManager.hpp>
#include <iostream>
#include <vector>
using namespace VMath;

// TODO: Add info panel, on mouse rollover and on click. use some lorem ipsum
// for now. Billborad textures? or will shapes work fine? (with alpha, ofc), use lined rectangel, shape example


int main(void)
{
  // initialize
  Window window;
  Ray ray;

  CameraManager cm = CameraManager::instance();
  
  // planets
  Planet mercury { "res/models/mercury/mercuryBuilt.obj", "res/textures/mercury/mercury_albedo.png", Vector3 { 0.0, 0.0, 0.0}, 1.0f };
  Planet venus { "res/models/venus/venusBuilt.obj", "res/textures/venus/2k_venus_atmosphere.png", Vector3 { 30.0, 0.0, 0.0}, 1.0f };
  Planet earth { "res/models/earth/earth.obj", "res/textures/earth/earth_albedo.png", Vector3 {60.0,0.0, 0.0}, 0.1f};
  Planet mars { "res/models/mars/marsBuilt.obj", "res/textures/mars/mars.png" , Vector3 { 90.0, 0.0, 0.0}, 1.0f};
  Planet jupiter { "res/models/jupiter/jupiterBuilt.obj", "res/textures/jupiter/2k_jupiter.png", Vector3 { 120.0, 0.0,  0.0}, 1.0f};
  Planet saturn { "res/models/saturn/saturnBuilt.obj", "res/textures/saturn/2k_saturn.png", Vector3 { 150.0, 0.0, 0.0}, 1.0f};
  Planet uranus { "res/models/uranus/uranusBuilt.obj", "res/textures/uranus/2k_uranus.png", Vector3 { 180.0, 0.0, 0.0}, 1.0f};
  Planet neptune { "res/models/neptune/neptuneBuilt.obj", "res/textures/neptune/2k_neptune.png", Vector3 { 210.0, 0.0, 0.0}, 1.0f};  
  
  SetTargetFPS(60);               // target 60 fps
  // Main game loop
  while (!WindowShouldClose())    // Detect window close button or ESC key
    {
      // Update
      cm.Update();
      
      ray = GetMouseRay(GetMousePosition(), cm.getCamera());

      // update plaents
      mercury.CheckPointer(ray);
      mercury.Update();
      venus.CheckPointer(ray);
      venus.Update();
      earth.CheckPointer(ray);
      earth.Update();
      mars.CheckPointer(ray);
      mars.Update();
      jupiter.CheckPointer(ray);
      jupiter.Update();
      saturn.CheckPointer(ray);
      saturn.Update();
      uranus.CheckPointer(ray);
      uranus.Update();
      neptune.CheckPointer(ray);
      neptune.Update();
      
      
      if(mercury.getClicked())
	cm.setTarget(&mercury);
      else if(venus.getClicked())
	cm.setTarget(&venus);
      else if(earth.getClicked())
	cm.setTarget(&earth);
      else if(mars.getClicked())
	cm.setTarget(&mars);
      else if(jupiter.getClicked())
	cm.setTarget(&jupiter);
      else if(saturn.getClicked())
	cm.setTarget(&saturn);
      else if(uranus.getClicked())
	cm.setTarget(&uranus);
      else if(neptune.getClicked())
	cm.setTarget(&neptune);

      

      if (IsKeyPressed(KEY_Q))
	{
	  cm.unsetTarget();
	}
      
      // Draw
      BeginDrawing();
      BeginMode3D(cm.getCamera());
       
      ClearBackground(BLACK);

      // draw all the planets
      mercury.Draw();
      venus.Draw();
      earth.Draw();
      mars.Draw();
      jupiter.Draw();
      saturn.Draw();
      uranus.Draw();
      neptune.Draw();
      
      EndMode3D();

      // better place to put this?
      mercury.DisplayInfo();
      venus.DisplayInfo();
      earth.DisplayInfo();
      mars.DisplayInfo();
      jupiter.DisplayInfo();
      saturn.DisplayInfo();
      uranus.DisplayInfo();
      neptune.DisplayInfo();
      
      EndDrawing();
      
    }

  return 0;
}



