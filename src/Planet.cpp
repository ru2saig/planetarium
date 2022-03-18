#include <raylib.h>
#include <Planet.hpp>
#include <PVector3.hpp>
using namespace VMath;

float Planet::BASE_PLANET_RADIUS = 10.0f;

// TODO: How to set other materials? like emission
//       How to add more models, with their own textures


Planet::Planet(string model_path, string texture_path, Vector3 pos,  float scale)
  : scale { scale }, planetClicked { false }, radius { scale * BASE_PLANET_RADIUS} 
{
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
  DrawModel(this->model, this->pos, this->scale, WHITE);
  DisplayInfo();
}

void Planet::Update() 
{
  // Updating bounding box: make new bounding box each time
  // TODO: is it possible to get the radius of the sphere from mesh data?
  
  // do physics here
  // what physics?
  // rotation on axis (how?) model.transform <- MatrixRotateXYZ((Vector3){  });
  // rotation around the sun (how?)
  pos = pos + (Vector3) {0.1f, 0.0f, 0.0f};
  
}

// check if the pointer entered the vicinity and the mesh itself
void Planet::CheckPointer(Ray mouse)
{
 
  // planetClicked is used to check if the planet was clicked on
  planetEntered = GetRayCollisionSphere(mouse, this->pos, 10.0f);
  if ((planetEntered.hit) && (planetEntered.distance < FLT_MAX))
    { // mouseover the planet

      // check if planet is clicked
      RayCollision planetModelClicked = GetRayCollisionSphere(mouse, this->pos, 10.0f);
      if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && planetModelClicked.hit)
	planetClicked = true;
      else
	planetClicked = false;
    }
  
}

// display info in a panel near the planet
// TODO: info panel DrawRecLines or somthn
void Planet::DisplayInfo()
{
  if(planetEntered.hit and !planetClicked)
    { // only display general info if planet is not clicked
      //DrawSphere(this->pos, 10.0f, RED);
    } else if(planetClicked and planetEntered.hit)
    {
      DrawSphere(this->pos, 10.0f, RED);
    }  
}


