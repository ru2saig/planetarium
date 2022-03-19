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
  std::vector<Planet> planets; // put em in a vector?
  planets.reserve(9);
  Planet mercury {"res/models/mercury/mercury.obj", "res/textures/mercury/mercury_albedo.png", Vector3 { 0.0, 0.0, 0.0}, 10.0f };
  planets[0] = mercury;
  //planets[1] = Planet {"res/models/venus/venusBuilt.obj", "res/textures/venus/2k_venus_atmosphere.png", Vector3 { 0.0, 50.0, 0.0}, 1.0f };
  //planets[2] = new Planet {"res/models/earth/earth.obj", "res/textures/earth/earth_albedo.png", Vector3 {0.0, 100.0, 0.0}, 1.0f};
  

  
  std::cerr << "Initialized" << std::endl;
  SetTargetFPS(60);               // target 60 fps
  // Main game loop
  while (!WindowShouldClose())    // Detect window close button or ESC key
    {

      // Update
      cm.Update();
      
      ray = GetMouseRay(GetMousePosition(), cm.getCamera());


      for(Planet& planet : planets)
	{
	  planet.CheckPointer(ray);
	  planet.Update();

	  if(planet.getClicked())
	    {
	      //cm.unsetTarget(); 
	      cm.setTarget(&planet);
	    }
	}

      if (IsKeyPressed(KEY_Q))
	{
	  cm.unsetTarget();
	}
      
      // Draw
      BeginDrawing();
      BeginMode3D(cm.getCamera());
       
      ClearBackground(BLACK);

      for(Planet& planet : planets)
	planet.Draw();
      
      EndMode3D();
		   

      // better place to put this?
      for(Planet& planet : planets)
	planet.DisplayInfo();
      
      EndDrawing();
      
    }

  return 0;
}



