#include <Earth.hpp>
#include <raylib.h>
#include <rlgl.h>
#include <fstream>
#include <Utility.hpp>
#include <Orbit.hpp>
#include <cstdlib>
#include <iostream>
#include <raygui.hpp>

Earth::Earth(Camera* camera)
{
  this->camera = camera;
  this->radius = 10.0f;
  this->clicked = false;
  this->pos =  Vector3 {5000.0f ,0.0, 0.0}; // TODO This will cause concerns,
  this->orbit = Orbit(this->pos.x, 6000.0, Vector3 { 0.0f, 0.0f, 0.0f });
  
  this->model = LoadModel("res/models/earth/earthmesh.obj");
  shader = LoadShader("res/shaders/planet-default.vs", "res/shaders/earth.fs");
  shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");

  std::string info_path = "res/info/earth/earth";
  
  switch(GlobalFonts::GlobalFontInstance().returnCurrentLang())
    {
    case Lang::ENGLISH:
      info_path += "-en";
      break;
    case Lang::HINDI:
      info_path += "-hi";
      break;
    case Lang::TELUGU:
      info_path += "-te";
      break;
    }
  
  std::fstream info { info_path };
  if(!info) {
    std::cerr << "[FAILED IO] Failed to open file: " << info_path << std::endl;
  } else {
    std::cerr << "[FILE IO] Successfully opened file: " << info_path << std::endl;

    info.getline(planetName, 256);
    info.getline(planetInfo, 1024);
    info.getline(mass, 256);
    info.getline(volume, 256);
    info.getline(gravity, 256);
    info.getline(escape_velocity, 256);
    info.getline(no_of_natural_satellites, 256);
    info.getline(moment_of_inertia, 256);
    info.getline(diamteter, 256);
    info.getline(perihelion, 256);
    info.getline(aphelion, 256);
    info.getline(length_of_day, 256);
    info.getline(avg_temp, 256);
    info.getline(orbital_period, 256);
    info.getline(orbital_vel, 256);
    info.getline(mean_orbital_vel, 256);

    
  }

  Utility::Light sunLight = { (Vector3) { 2, 1, 2}, WHITE }; 
  sunLight.ambientStrength = (Vector4) { 0.01, 0.01, 0.01, 1.0};
  sunLight.colorLoc = GetShaderLocation(shader, "sun.color");
  sunLight.positionLoc = GetShaderLocation(shader, "sun.position");

  
  float position[3] = { sunLight.position.x, sunLight.position.y, sunLight.position.z };
  SetShaderValue(shader, sunLight.positionLoc, position, SHADER_UNIFORM_VEC3);

  float color[4] = { (float)sunLight.color.r/(float)255, (float)sunLight.color.g/(float)255, 
		     (float)sunLight.color.b/(float)255, (float)sunLight.color.a/(float)255 };
  SetShaderValue(shader,  sunLight.colorLoc, color, SHADER_UNIFORM_VEC4);
  // Ambient light level
  int ambientLoc = GetShaderLocation(shader, "sun.ambientStrength");
  float ambientStrength[4] = { sunLight.ambientStrength.x, sunLight.ambientStrength.y, sunLight.ambientStrength.z, sunLight.ambientStrength.w};
  SetShaderValue(shader, ambientLoc, ambientStrength, SHADER_UNIFORM_VEC4);

  // set the shader as the current material shader
  model.materials[0].shader = shader;
  // load and set the textures
  model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = LoadTexture("res/textures/earth/earth_albedo.png");
  model.materials[0].maps[MATERIAL_MAP_SPECULAR].texture = LoadTexture("res/textures/earth/earthspec1k.png");
  model.materials[0].maps[MATERIAL_MAP_EMISSION].texture = LoadTexture("res/textures/earth/earth_night_lights_modified.png");
  shader.locs[SHADER_LOC_MAP_EMISSION] = GetShaderLocation(shader, "texture2"); // required to access it as an emssion texture

}


void Earth::Draw()
{
  if(showHitBox)
    DrawSphere(this->pos,  this->radius, Color { 255, 0, 0, 50});

  if(showOrbit)
    this->orbit.Draw();

  DrawModel(this->model, this->pos, this->radius * 1.5, WHITE);
}

void Earth::Update()
{
  float cameraPos[3] { camera->position.x, camera->position.y, camera->position.z };
  SetShaderValue(shader,  GetShaderLocation(shader, "viewPos"), cameraPos, SHADER_UNIFORM_VEC3);

  pos = orbit.Evaluate();
  orbit.Update();
}

