#include <raylib.h>
#include <Sun.hpp>
#include <PVector3.hpp>

#include <iostream>
using namespace VMath;

// TODO: How to set other materials? like emission
//       How to add more models, with their own textures

Sun::Sun(string model_path, string texture_path)
{
  this->radius = 100.0f;
  this->clicked = false;
  this->pos = Vector3 { -150.0f, 0.0f, 0.0f }; // TODO: Change this back, before doing orbits
  model = LoadModel(model_path);
  texture = LoadTexture(texture_path);
  model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
}

Sun::~Sun()
{
  UnloadTexture(texture);
  UnloadModel(model);
}

void Sun::Draw()
{
  DrawSphere(this->pos,  this->radius, Color { 255, 0, 0, 50});
  DrawModel(this->model, this->pos, this->radius * 1.5, WHITE);
}

void Sun::Update() 
{
  // the sun shall sit there ominously, making ominous noises
  
  // do physics here
  // what physics?
  // rotation on axis (how?) model.transform <- MatrixRotateXYZ((Vector3){  });
  // rotation around the sun (how?)
  // pos = pos + (Vector3) {0.1f, 0.0f, 0.0f};
}

// check if the pointer entered the vicinity and the mesh itself
void Sun::CheckPointer(Ray mouse)
{
 
  // sunClicked is used to check if the sun was clicked on
  sunEntered = GetRayCollisionSphere(mouse, this->pos, this->radius);
  if ((sunEntered.hit) && (sunEntered.distance < FLT_MAX))
    { // mouseover the sun

      // check if sun is clicked
      RayCollision sunModelClicked = GetRayCollisionSphere(mouse, this->pos, this->radius);
      if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && sunModelClicked.hit)
	clickedTrue();
    }
}

// display info in a panel near the sun
void Sun::DisplayInfo()
{
  if(sunEntered.hit and !clicked)
    { // only display general info if sun is not clicked
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


