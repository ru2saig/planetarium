#include <CelestialBody.hpp>
#include <Skybox.hpp>
#include <raylib.h>
#include <rlgl.h>
#include <PVector3.hpp>
#include <Planet.hpp>
#include <Earth.hpp>
#include <Sun.hpp>
#include <Window.hpp>
#include <CameraManager.hpp>
#include <vector>
#include <memory>
#include <raygui.h>
using namespace VMath;

int main(void)
{
  // initialize
  Window window;
  Ray ray;

  CameraManager cm = CameraManager::instance();
  Skybox skybox = Skybox::instance();

    // setting up the camera flare shader
  Shader cameraFlarePP = LoadShader(0, "res/shaders/sunflare.fs"); // eh-he

  // set the noise texture
  int noiseLoc = GetShaderLocation(cameraFlarePP, "noiseTex");
  Texture noiseTexture = LoadTexture("res/textures/noise.png");

  // set the inital sun position
  int sunPosLoc = GetShaderLocation(cameraFlarePP, "sunPos");
  float sunPos[2] = {GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};
  SetShaderValue(cameraFlarePP, sunPosLoc, sunPos, SHADER_UNIFORM_VEC2);
  
  // screen resolution
  int screenResLoc = GetShaderLocation(cameraFlarePP, "screenRes");
  float res[2] = { static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight()) };
  SetShaderValue(cameraFlarePP, screenResLoc, res, SHADER_UNIFORM_VEC2);
  
  // set the resolution of said noise texture
  int noiseResLoc = GetShaderLocation(cameraFlarePP, "noiseResolution");
  float noiseRes[2] = { static_cast<float>(noiseTexture.width), static_cast<float>(noiseTexture.height) };
  SetShaderValue(cameraFlarePP, noiseResLoc, noiseRes, SHADER_UNIFORM_VEC2);

  // the sun radius
  int sunRadiusLoc = GetShaderLocation(cameraFlarePP, "radius");
  float radius[1] = { 16.0 };
  SetShaderValue(cameraFlarePP, sunRadiusLoc, radius, SHADER_UNIFORM_FLOAT);
  
  RenderTexture2D target = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

  int index = 0;
  int val = 0;
  GuiListView(Rectangle { 0, 0, 100, 100}, "Hello;there;hee", &index, val);
  
  // planets
  // 1 pixel = 100,000 km (way to large)
  // all planets are set to scale in reference to the Earth

  std::vector<std::unique_ptr<Planet>> planets;

  planets.emplace_back(new Planet("res/models/mercury/mercuryBuilt.obj", "res/textures/mercury/mercury_albedo.png", "res/info/mercury/mercury.txt", Vector3 { 140.0, 0.0, 0.0}, 0.33f, 142.0f));
  planets.emplace_back(new Planet("res/models/venus/venusBuilt.obj", "res/textures/venus/2k_venus_atmosphere.png", "res/info/venus/venus.txt", Vector3 { 220.0, 0.0, 0.0}, 0.94f, 375.0f));
  // Make an Earth class, for this
  //planets.emplace_back(new Planet("res/models/earth/earthBuilt.obj", "res/textures/earth/earth_albedo.png", "res/info/earth/earth.txt", Vector3 {500.0f ,0.0, 0.0}, 1.0f, 600.0));
  planets.emplace_back(new Earth((cm.getCameraPtr())));
  planets.emplace_back(new Planet( "res/models/mars/marsBuilt.obj", "res/textures/mars/mars.png" , "res/info/mars/mars.txt", Vector3 { 600.0, 0.0, 0.0}, 0.5f, 900.0));
  planets.emplace_back(new Planet("res/models/jupiter/jupiterBuilt.obj", "res/textures/jupiter/2k_jupiter.png", "res/info/jupiter/jupiter.txt", Vector3 { 800.0, 0.0,  0.0}, 11.0f, 7142.0f));
  planets.emplace_back(new Planet("res/models/saturn/saturnBuilt.obj", "res/textures/saturn/2k_saturn.png", "res/info/saturn/saturn.txt", Vector3 { 1000.0, 0.0, 0.0}, 9.0f, 17647.0f));
  planets.emplace_back(new Planet("res/models/uranus/uranusBuilt.obj", "res/textures/uranus/2k_uranus.png", "res/info/uranus/uranus.txt", Vector3 { 1200.0, 0.0, 0.0}, 4.0f, 50000.0f));
  planets.emplace_back(new Planet("res/models/neptune/neptuneBuilt.obj", "res/textures/neptune/2k_neptune.png", "res/info/neptune/neptune.txt", Vector3 { 1300.0, 0.0, 0.0}, 3.9f, 100000.0f));

  // sun
  Sun sun { "res/models/sun/sunBuilt.obj", "res/textures/sun/2k_sun.png" }; // the sun is at the centre of the Unierse. Galieo rollin' in his grave

  bool debugMenu = false;

  SetTargetFPS(60);               // target 60 fps
  // Main game loop
  while (!WindowShouldClose())    // Detect window close button or ESC key
    {
      // Update
      cm.Update();

      // TODO: smol bug, appears in the middle of the screen
      // get the sun's screen coords, and send em to the shader
      Vector2 sunScreenCoords = GetWorldToScreen(Vector3Zero(), cm.getCamera());
      if(!std::isnan(sunScreenCoords.x))
	sunPos[0] = sunScreenCoords.x;

      if(!std::isnan(sunScreenCoords.y))
	sunPos[1] = GetScreenHeight() - sunScreenCoords.y;
    
      SetShaderValue(cameraFlarePP, sunPosLoc, sunPos, SHADER_UNIFORM_VEC2);

      // make the size of the sun proportionate to the distance
      Vector3 camPos = cm.getCamera().position;
      float distFromSun = std::sqrt(camPos.x*camPos.x + camPos.y+camPos.y + camPos.z*camPos.z);

      radius[0] = std::min(300.0f, std::max(16.0f, distFromSun/10.0f));
    
      SetShaderValue(cameraFlarePP, sunRadiusLoc, radius, SHADER_UNIFORM_FLOAT);

      
      ray = GetMouseRay(GetMousePosition(), cm.getCamera());
      // update celestial bodies


      if(IsKeyPressed(KEY_F3))
	 debugMenu = !debugMenu;
      
      for(std::vector<std::unique_ptr<Planet>>::iterator planet = planets.begin(); planet != planets.end(); planet++)
	{
	  planet->get()->CheckPointer(ray);
	  planet->get()->Update();

	  if(planet->get()->getClicked())
	    cm.setTarget(planet->get());
	}


      if(IsKeyPressed(KEY_Q))
	cm.unsetTarget();
      
      if(debugMenu)
	{
	  Planet::toggleShowOrbit();
	  Planet::toggleShowHitBox();
	}

      
      // Draw
      BeginTextureMode(target);
      ClearBackground(BLACK);
      
      BeginMode3D(cm.getCamera());
      skybox.Draw();

      // draw all the planets
      for(auto& planet : planets)
	planet->Draw();
      
      if(debugMenu)
	DrawGrid(100, 5.0f);
      
      EndMode3D();
      EndTextureMode();

      // post processing effects, mainly the camera flare and the Sun
      BeginDrawing();
      ClearBackground(BLACK);

      BeginShaderMode(cameraFlarePP); // eh-he
      SetShaderValueTexture(cameraFlarePP, noiseLoc, noiseTexture);
      DrawTextureRec(target.texture, (Rectangle){ 0, 0, (float)target.texture.width, (float)-target.texture.height }, (Vector2){ 0, 0 }, WHITE);
      EndShaderMode();

      // Draw text and 2D stuff here
      if(debugMenu)
	DrawFPS(10, 10);

         
      for(auto& planet: planets)
	planet->DisplayInfo();
      sun.DisplayInfo();


            
      EndDrawing();
      
    }


  UnloadShader(cameraFlarePP);
  UnloadTexture(noiseTexture);

  
  return 0;
}



