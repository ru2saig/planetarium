#include <raylib.h>
#include <Planet.hpp>
#include <PVector3.hpp>
using namespace VMath;

#include <iostream>

// TODO: How to set other materials? like emission
//       How to add more models, with their own textures

Planet::Planet(string model_path, string texture_path, Vector3 pos,  float scale)
  : pos { pos }, scale { scale }, planetClicked { true }
    
{
  model = LoadModel(model_path);
  texture = LoadTexture(texture_path);
  model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
  box = GetMeshBoundingBox(model.meshes[0]);    // get the bounding box
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


  std::cerr << "POS" << pos.x << ", " << pos.y << ", " << pos.z << std::endl;
  std::cerr << "BOX MIN" << box.min.x << ", " << box.min.y << ", " << box.min.z << std::endl;
  std::cerr << "BOX MAX" << box.max.x << ", " << box.max.y << ", " << box.max.z << std::endl;
  
  // do physics here
  // what physics?
  // rotation on axis (how?) model.transform <- MatrixRotateXYZ((Vector3){  });
  // rotation around the sun (how?)
  pos = pos + (Vector3) {0.1f, 0.0f, 0.0f};
  
}

// check if the pointer entered the vicinity and the mesh itself
void Planet::CheckPointer(Ray mouse)
{
  // boundingBoxEntered is used to check if the  mouse enters the bounding box
  // planetClicked is used to check if the planet was clicked on
  boundingBoxEntered = GetRayCollisionBox(mouse, box);
  if ((boundingBoxEntered.hit) && (boundingBoxEntered.distance < FLT_MAX))
    { // mouseover the bounding box

      // check if planet is clicked
      RayCollision planetModelClicked = GetRayCollisionModel(mouse, model);
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
  if(boundingBoxEntered.hit and !planetClicked)
    { // only display general info if planet is not clicked
      DrawBoundingBox(box, RED); // TODO: change cursosr will probably require a refactor
    } else if(planetClicked and boundingBoxEntered.hit)
    {
     
      DrawBoundingBox(box, WHITE);
    }  
}


