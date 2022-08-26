#include "raygui.hpp"
#include <raylib.h>
#include <Utility.hpp>
#include <GUIUtil.hpp>
#include <Orbit.hpp>
#include <Planet.hpp>
#include <PVector3.hpp>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iostream>
using namespace VMath;

float Planet::BASE_PLANET_RADIUS = 10.0f;
bool Planet::showOrbit = false;
bool Planet::showHitBox = false;



Planet::Planet(string model_path, string texture_path, std::string info_path, Vector3 pos,
               float radius, float orbitPeriod)
{
  GlobalFonts gb = GlobalFonts::GlobalFontInstance();
  
  this->radius = radius * Planet::BASE_PLANET_RADIUS;
  this->clicked = false;
  this->pos = pos;
  // TODO: why should this work? why is it not? (without the center argumetn)
  this->orbit = Orbit(this->pos.x, orbitPeriod, Vector3 { 0.0f, 0.0f, 0.0f });

  // TODO: Add the suffix, depending on the currently selectd language
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
    case Lang::MARATHI:
      info_path += "-ma";
      break;
    }

  
  std::fstream info { info_path };
  if(!info) {
    std::cerr << "[FAILED IO] Failed to open file: " << info_path << std::endl;
  } else {
    std::cerr << "[FILE IO] Successfully opened file: " << info_path << std::endl;
    info.getline(planetName, 256);


    char planet_Info[1024];
    info.getline(planet_Info, 1024);
    planetInfo = Utility::WrapText(planet_Info, GlobalFonts::GlobalFontInstance().getSize());
    
    
    
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
  
  model = LoadModel("res/models/earth/earthmesh.obj");
  //model = LoadModel(model_path);

  // load the default planet shader
  // TODO: Since all the planets (except earth) use this, why not make this the default one? Perhaps a singleton?
  shader = LoadShader("res/shaders/planet-default.vs", "res/shaders/planet-default.fs");
  shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(shader, "viewPos");
  
  Utility::Light sunLight = { (Vector3) { 2, 1, 2}, WHITE }; 
  sunLight.ambientStrength = (Vector4) { 0.001, 0.001, 0.001, 1.0};
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
  model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = LoadTexture(texture_path);
  
}

Planet::~Planet()
{  
  UnloadModel(model);
  UnloadShader(shader);
}

void Planet::Draw()
{
  if(showHitBox)
    DrawSphere(this->pos,  this->radius, Color { 255, 0, 0, 50});

  if(showOrbit)
    this->orbit.Draw();

  DrawModel(this->model, this->pos, this->radius * 1.5, WHITE);
}


void Planet::Update(Camera* camera) 
{

  float cameraPos[3] { camera->position.x, camera->position.y, camera->position.z };
  SetShaderValue(shader,  GetShaderLocation(shader, "viewPos"), cameraPos, SHADER_UNIFORM_VEC3);
  
  pos = orbit.Evaluate();
  orbit.Update();
  // TODO: is it possible to get the radius of the sphere from mesh data?
  
  // do physics here
  // what physics?
  // rotation on axis (how?) model.transform <- MatrixRotateXYZ((Vector3){  });
  // rotation around the sun (how?)
  // pos = pos + (Vector3) {0.1f, 0.0f, 0.0f};
}



void Planet::Update() 
{
  pos = orbit.Evaluate();
  orbit.Update();
  // TODO: is it possible to get the radius of the sphere from mesh data?
  
  // do physics here
  // what physics?
  // rotation on axis (how?) model.transform <- MatrixRotateXYZ((Vector3){  });
  // rotation around the sun (how?)
  // pos = pos + (Vector3) {0.1f, 0.0f, 0.0f};
}



// check if the pointer entered the vicinity and the mesh itself
void Planet::CheckPointer(Ray mouse)
{
 
  // planetClicked is used to check if the planet was clicked on
  planetEntered = GetRayCollisionSphere(mouse, this->pos, this->radius);
  if ((planetEntered.hit) && (planetEntered.distance < FLT_MAX))
    { // mouseover the planet

      // check if planet is clicked
      RayCollision planetModelClicked = GetRayCollisionSphere(mouse, this->pos, this->radius);
      if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && planetModelClicked.hit)
	clickedTrue();
    }
}

// display info in a panel near the planet
void Planet::DisplayInfo() 
{
  if(planetEntered.hit && !clicked)
     { // only display general info if planet is not clicked
       // TODO: play voice-to-text here
       // normal info
       std::cerr << "[PLAYING INFO FOR ]: " << this <<  std::endl; 

       //GuiSetFont(GlobalFonts::GlobalFontInstance().returnCurrentFont());
       //DrawTextBoxed(GlobalFonts::GlobalFontInstance().returnCurrentFont(), planetInfo , Rectangle { GetScreenWidth() - 250.0f, 0, 250, 500}, 30, 0, true, WHITE);
  //      // RGuiTextBoxMulti(0, GetScreenWidth() - 250, 0, 250, GetScreenHeight()/2.0, TextFormat("%s\n%s\n", planetName, planetInfo)).DrawControl();
       Utility::DrawTextBox(GetScreenWidth() - 400, 0, 400, 400, "%s\n%s\n", planetName, planetInfo);

      }
  else if(clicked)
    { // display a lot of info
      std::cerr << "[PLAYING EXTRA INFO FOR ]: " << this <<  std::endl; 


      Utility::DrawTextBox(GetScreenWidth() - 400, 0, 400, 500, "Mass: %s 10^24kg\nVolume: %s 10^10 km^3\nGravity: %s m/s^2\nEscape Velocity: %s km/s\nNatural Satellites: %s\nMoment of Inertia: %s I/MR^2\nDiameter: %s km\nPerihelion: %s 10^6 km\nAphelion: %s 10^6 km\nLength of Day: %s hr(s)\nAverage Temperature: %s C\nOrbital Period: %s days\nOrbital Velocity: %s km/s\nMean Orbital Velocity: %s km/s\n" , mass, volume, gravity, escape_velocity, no_of_natural_satellites, moment_of_inertia, diamteter, perihelion, aphelion, length_of_day, avg_temp, orbital_period, orbital_vel, mean_orbital_vel);
      
    }
      // DrawRectangle(0, 0, 250, 400, BLACK); // TODO: add a little transparency, and make it gray
      // DrawRectangleLines(0, 0, 250, 400, WHITE);

      // int pos_x = 4;
      // int pos_y = 4;
      // int text_height = 13;



      
      // // I seek for forgivness from thee, oh gods of programming
      // DrawText(mass, pos_x, pos_y, text_height, WHITE);
      // pos_y += text_height;
      // DrawText(volume, pos_x, pos_y, text_height, WHITE);
      // pos_y += text_height;
      // DrawText(gravity, pos_x, pos_y, text_height, WHITE);
      // pos_y += text_height;
      // DrawText(gravity, pos_x, pos_y, text_height, WHITE);
      // pos_y += text_height;
      // DrawText(escape_velocity, pos_x, pos_y, text_height, WHITE);
      // pos_y += text_height;
      // DrawText(no_of_natural_satellites, pos_x, pos_y, text_height, WHITE);
      // pos_y += text_height;
      // DrawText(moment_of_inertia, pos_x, pos_y, text_height, WHITE);
      // pos_y += text_height;
      // DrawText(diamteter, pos_x, pos_y, text_height, WHITE);
      // pos_y += text_height;
      // DrawText(perihelion, pos_x, pos_y, text_height, WHITE);
      // pos_y += text_height;
      // DrawText(aphelion, pos_x, pos_y, text_height, WHITE);
      // pos_y += text_height;
      // DrawText(length_of_day, pos_x, pos_y, text_height, WHITE);
      // pos_y += text_height;
      // DrawText(avg_temp, pos_x, pos_y, text_height, WHITE);
      // pos_y += text_height;
      // DrawText(orbital_period, pos_x, pos_y, text_height, WHITE);
      // pos_y += text_height;
      // DrawText(orbital_vel, pos_x, pos_y, text_height, WHITE);

    // }  
}
