#include <raylib.h>
#include <Sun.hpp>
#include <PVector3.hpp>
#include <Utility.hpp>

#include <iostream>
using namespace VMath;

Sun::Sun(string model_path, string texture_path)
{
  this->radius = 100.0f;
  this->clicked = false;
  this->pos = Vector3 { 0.0f, 0.0f, 0.0f }; // Galieo rollin' in his grave

  sunInfo = Utility::WrapText("The Sun is the star at the center of the Solar System. It is a nearly perfect ball of hot plasma,heated to incandescence by nuclear fusion reactions in its core, radiating the energy mainly as visible light, ultraviolet light, and infrared radiation.It is by far the most important source of energy for life on Earth." ,LINE_LENGTH_SMALL);
  
  
  model = LoadModel(model_path);
  texture = LoadTexture(texture_path);
  model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
}

Sun::~Sun()
{
  free(sunInfo);
  UnloadTexture(texture);
  UnloadModel(model);
}

void Sun::Draw()
{
  //  DrawSphere(this->pos,  this->radius, Color { 255, 0, 0, 50});
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
      // TODO: Put this into a variable and use wrapText
      Utility::DrawTextBox(0, 0, 250, 250, sunInfo);
    }
  else if(clicked)
    { // display a lot of info
      // TODO: Put the info into some variable and use wrapText
      Utility::DrawTextBox(0, 0, 250, 250, "\n");
    }  
}


