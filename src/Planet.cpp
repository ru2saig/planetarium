#include <utils.h>
#include <raylib.h>
#include <Planet.hpp>

Planet::Planet(string model_path, string texture_path, Vector3 pos,  float scale)
  : pos { pos }, scale { scale }
    
{
  model = LoadModel(model_path);
  texture = LoadTexture(texture_path);
  model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
  box = GetMeshBoundingBox(model.meshes[0]);    // Get mesh bounding box
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
  // do physics
  // what physics?
  // rotation on axis (how?) model.transform <- MatrixRotateXYZ((Vector3){  });
  // rotation around the sun (how?)

}

// check if pointer entered the mesh, and set things accordingly
// https://www.raylib.com/examples/models/loader.html?name=models_yaw_pitch_roll
void Planet::CheckPointer(Ray mouse)
{
  // boundingBoxEntered is used to check if the  mouse enters the bounding box
  // planetClicked is used to check if the planet was clicked on
  boundingBoxEntered = GetRayCollisionBox(mouse, box);
  if ((boundingBoxEntered.hit) && (boundingBoxEntered.distance < FLT_MAX))
    {
      // mouse entered bounding box


      planetClicked = GetRayCollisionModel(mouse, model);
      // TODO: check if clicked?
      // TODO: Use TRACE_LOG
      
    }
  
}

// display info in a panel near the planet
// TODO: use .hit of RayCOllision struct to check, this should be done in draw
// TODO: info panel DrawRecLines or somthn
void Planet::DisplayInfo()
{
  if(boundingBoxEntered.hit)
    {
      DrawBoundingBox(box, RED);
      TRACELOG(LOG_INFO, "PLANET: [%p] Planet bounding box entered", this);
    }
	       
  
}


