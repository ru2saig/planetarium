#include <raylib.h>
#include <Planet.hpp>
#include <PVector3.hpp>

#include <iostream>
using namespace VMath;

float Planet::BASE_PLANET_RADIUS = 10.0f;

// TODO: How to set other materials? like emission
//       How to add more models, with their own textures

Planet::Planet(string model_path, string texture_path, Vector3 pos,  float radius)
{
  this->radius = radius * Planet::BASE_PLANET_RADIUS;
  this->clicked = false;
  this->pos = pos;
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
  DrawSphere(this->pos,  this->radius, Color { 255, 0, 0, 50});
  DrawModel(this->model, this->pos, this->radius * 1.5, WHITE);
}

void Planet::Update() 
{
  // Updating bounding box: make new bounding box each time
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
  if(planetEntered.hit and !clicked)
    { // only display general info if planet is not clicked
      DrawRectangle(0, 0, 250, 250, BLACK); // TODO: add a little transparency, and make it gray
      DrawRectangleLines(0, 0, 250, 250, WHITE);
      DrawText("lorem ipsum salt and pepper too", 10, 10, 13, WHITE);
    }
  else if(clicked)
    { // display a lot of info
      //DrawSphere(this->pos,  this->radius + 5.0f, PINK);


      DrawRectangle(0, 0, 250, 250, BLACK); // TODO: add a little transparency, and make it gray
      DrawRectangleLines(0, 0, 250, 250, WHITE);
      DrawText("if sally sells seashells by the seashore, does that", 10, 10, 13, WHITE);
      DrawText("make here a carpitalist?", 10, 20, 13, WHITE);      
    }  
}


