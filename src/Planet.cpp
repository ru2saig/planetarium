#include <raylib.h>
#include <Planet.hpp>
// TODO: Make a celestial body class? And then make a planet, star, asteroid, etc from that

Planet::Planet(string model_path, string texture_path, Vector3 pos,  float scale)
  : pos { pos }, scale { scale }
{
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
}

void Planet::Update() 
{
  // do physics
  // what physics?
  // rotation on axis (how?) model.transform <- MatrixRotateXYZ((Vector3){  });
  // rotation around the sun (how?)
  
}

// check if user clicks the planet
// https://www.raylib.com/examples/models/loader.html?name=models_yaw_pitch_roll
bool Planet::IsClicked() {}



