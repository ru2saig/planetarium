#include <raylib.h>
#include <Orbit.hpp>
#include <Planet.hpp>
#include <PVector3.hpp>
#include <fstream>
#include <iostream>
using namespace VMath;

float Planet::BASE_PLANET_RADIUS = 10.0f;
bool Planet::showOrbit = false;
bool Planet::showHitBox = false;

Planet::Planet(string model_path, string texture_path, string info_path, Vector3 pos,
               float radius, float orbitPeriod)
{
  this->radius = radius * Planet::BASE_PLANET_RADIUS;
  this->clicked = false;
  this->pos = pos;
  // TODO: why should this work? why is it not? (without the center argumetn)
  this->orbit = Orbit(this->pos.x, orbitPeriod, Vector3 { 0.0f, 0.0f, 0.0f });
  
  std::fstream info { info_path };
  if(!info) {
    std::cerr << "[FAILED IO] Failed to open file: " << info_path << std::endl;
  } else {
    info.getline(planetName, 256);
    info.getline(planetInfo, 256);
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
  
  model = LoadModel(model_path);
  texture = LoadTexture(texture_path);
  model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
}

Planet::~Planet()
{
  UnloadTexture(texture);
  UnloadModel(model);
}

void Planet::Draw()
{
  if(showHitBox)
    DrawSphere(this->pos,  this->radius, Color { 255, 0, 0, 50});

  if(showOrbit)
    this->orbit.Draw();

  DrawModel(this->model, this->pos, this->radius * 1.5, WHITE);
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
      // TODO: for the information, add a way that auto-formats text, like a text box class
      DrawRectangle(0, 0, 250, 250, BLACK); // TODO: add a little transparency, and make it gray
      DrawRectangleLines(0, 0, 250, 250, WHITE);
      DrawText(planetName, 4, 4, 13, WHITE);
      DrawText(planetInfo, 4, 17, 13, WHITE);
    }
  else if(clicked)
    { // display a lot of info
      DrawRectangle(0, 0, 250, 400, BLACK); // TODO: add a little transparency, and make it gray
      DrawRectangleLines(0, 0, 250, 400, WHITE);

      int pos_x = 4;
      int pos_y = 4;
      int text_height = 13;

      // I seek for forgivness from thee, oh gods of programming
      DrawText(mass, pos_x, pos_y, text_height, WHITE);
      pos_y += text_height;
      DrawText(volume, pos_x, pos_y, text_height, WHITE);
      pos_y += text_height;
      DrawText(gravity, pos_x, pos_y, text_height, WHITE);
      pos_y += text_height;
      DrawText(gravity, pos_x, pos_y, text_height, WHITE);
      pos_y += text_height;
      DrawText(escape_velocity, pos_x, pos_y, text_height, WHITE);
      pos_y += text_height;
      DrawText(no_of_natural_satellites, pos_x, pos_y, text_height, WHITE);
      pos_y += text_height;
      DrawText(moment_of_inertia, pos_x, pos_y, text_height, WHITE);
      pos_y += text_height;
      DrawText(diamteter, pos_x, pos_y, text_height, WHITE);
      pos_y += text_height;
      DrawText(perihelion, pos_x, pos_y, text_height, WHITE);
      pos_y += text_height;
      DrawText(aphelion, pos_x, pos_y, text_height, WHITE);
      pos_y += text_height;
      DrawText(length_of_day, pos_x, pos_y, text_height, WHITE);
      pos_y += text_height;
      DrawText(avg_temp, pos_x, pos_y, text_height, WHITE);
      pos_y += text_height;
      DrawText(orbital_period, pos_x, pos_y, text_height, WHITE);
      pos_y += text_height;
      DrawText(orbital_vel, pos_x, pos_y, text_height, WHITE);

    }  
}
