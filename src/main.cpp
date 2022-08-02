#include "CelestialBody.hpp"
#include <raylib.h>
#include <rlgl.h>
#include <PVector3.hpp>
#include <Planet.hpp>
#include <Sun.hpp>
#include <Window.hpp>
#include <CameraManager.hpp>
#include <vector>
#include <memory>
using namespace VMath;

int main(void)
{
  // initialize
  Window window;
  Ray ray;

  CameraManager cm = CameraManager::instance();
  
  // planets
  // 1 pixel = 100,000 km (way to large)
  // all planets are set to scale in reference to the Earth

  std::vector<std::unique_ptr<Planet>> planets;

  planets.emplace_back(new Planet("res/models/mercury/mercuryBuilt.obj", "res/textures/mercury/mercury_albedo.png", "res/info/mercury/mercury.txt", Vector3 { 140.0, 0.0, 0.0}, 0.33f, 142.0f));
  planets.emplace_back(new Planet("res/models/venus/venusBuilt.obj", "res/textures/venus/2k_venus_atmosphere.png", "res/info/venus/venus.txt", Vector3 { 220.0, 0.0, 0.0}, 0.94f, 375.0f));
  // Make an Earth class, for this
  planets.emplace_back(new Planet("res/models/earth/earthBuilt.obj", "res/textures/earth/earth_albedo.png", "res/info/earth/earth.txt", Vector3 {500.0f ,0.0, 0.0}, 1.0f, 600.0));
  planets.emplace_back(new Planet( "res/models/mars/marsBuilt.obj", "res/textures/mars/mars.png" , "res/info/mars/mars.txt", Vector3 { 600.0, 0.0, 0.0}, 0.5f, 900.0));
  planets.emplace_back(new Planet("res/models/jupiter/jupiterBuilt.obj", "res/textures/jupiter/2k_jupiter.png", "res/info/jupiter/jupiter.txt", Vector3 { 800.0, 0.0,  0.0}, 11.0f, 7142.0f));
  planets.emplace_back(new Planet("res/models/saturn/saturnBuilt.obj", "res/textures/saturn/2k_saturn.png", "res/info/saturn/saturn.txt", Vector3 { 1000.0, 0.0, 0.0}, 9.0f, 17647.0f));
  planets.emplace_back(new Planet("res/models/uranus/uranusBuilt.obj", "res/textures/uranus/2k_uranus.png", "res/info/uranus/uranus.txt", Vector3 { 1200.0, 0.0, 0.0}, 4.0f, 50000.0f));
  planets.emplace_back(new Planet("res/models/neptune/neptuneBuilt.obj", "res/textures/neptune/2k_neptune.png", "res/info/neptune/neptune.txt", Vector3 { 1300.0, 0.0, 0.0}, 3.9f, 100000.0f));

  // sun
  Sun sun { "res/models/sun/sunBuilt.obj", "res/textures/sun/2k_sun.png" }; // the sun is at the centre of the Unierse. Galieo rollin' in his grave
  

  SetTargetFPS(60);               // target 60 fps
  // Main game loop
  while (!WindowShouldClose())    // Detect window close button or ESC key
    {
      // Update
      cm.Update();
      
      ray = GetMouseRay(GetMousePosition(), cm.getCamera());

      // update celestial bodies
      sun.CheckPointer(ray);
      sun.Update();      

      for(std::vector<std::unique_ptr<Planet>>::iterator planet = planets.begin(); planet != planets.end(); planet++)
	{
	  planet->get()->CheckPointer(ray);
	  planet->get()->Update();

	  if(planet->get()->getClicked())
	    cm.setTarget(planet->get());
	}

      if(sun.getClicked())
	cm.setTarget(&sun);
      
      if (IsKeyPressed(KEY_Q))
	  cm.unsetTarget();
      if(IsKeyPressed(KEY_D))
	Planet::toggleShowHitBox();
      if(IsKeyPressed(KEY_O))
	Planet::toggleShowOrbit();
      
      // Draw
      BeginDrawing();
      BeginMode3D(cm.getCamera());
       
      ClearBackground(BLACK);

      // draw all the planets
      for(auto& planet : planets)
	planet->Draw();
      
      sun.Draw();

      
      EndMode3D();

      // better place to put this?

      for(auto& planet: planets)
	planet->DisplayInfo();

      // mercury.DisplayInfo();
      // venus.DisplayInfo();
      // earth.DisplayInfo();
      // mars.DisplayInfo();
      // jupiter.DisplayInfo();
      // saturn.DisplayInfo();
      // uranus.DisplayInfo();
      // neptune.DisplayInfo();
      sun.DisplayInfo();
      
      EndDrawing();
      
    }

  return 0;
}



