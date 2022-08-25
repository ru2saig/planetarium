#include <cmath>
#include <raylib.h>
#include <math.h>
#include <CameraManager.hpp>
#include <memory>
#include <PVector3.hpp>
#include <CelestialBody.hpp>
#include <iostream>
#include <raymath.h>

using namespace VMath;



void CameraManager::Update()//Camera *camera)
{
  static Vector2 lastMousePos = { 0.0f, 0.0f };
  static bool firstMouse = true;
  static float yaw = 0.0f;
  static float pitch = 0.0f;
  static Vector3 cameraFront = Vector3{ 0.0f, 0.0f, -1.0f };
    
  const float cameraSpeed = 1.0f; 
     
  
  if(target) // follow target
    {
      float r = target->getRadius();
      cameraPtr->target = target->getPosition();
      cameraPtr->position = target->getPosition() + (Vector3) {r*2, r*2, r*2};
    }
  else 
    {      
      
      if(IsKeyDown(KEY_W))
	// TODO: Make an overloaded version of operator+=
	cameraPtr->position = cameraPtr->position + cameraSpeed * cameraFront;
      if(IsKeyDown(KEY_S))
	cameraPtr->position = cameraPtr->position - cameraSpeed * cameraFront;
      if(IsKeyDown(KEY_A))
       	cameraPtr->position = cameraPtr->position - Vector3Normalize(Vector3CrossProduct(cameraFront, cameraPtr->up));
      if(IsKeyDown(KEY_D))
	cameraPtr->position = cameraPtr->position + Vector3Normalize(Vector3CrossProduct(cameraFront, cameraPtr->up));



      if(IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT)) {
	// targeting in here?

	DisableCursor();
	Vector2 currentMousePos = GetMousePosition();
	
	if(firstMouse)
	  {
	    lastMousePos = currentMousePos;
	    firstMouse = false;
	  }

	float xoffset = currentMousePos.x - lastMousePos.x;
	float yoffset = lastMousePos.y - currentMousePos.y;

	lastMousePos = currentMousePos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;


	pitch = std::min(89.0f, std::max(pitch, -89.0f));

	Vector3 direction = {
	  cos(DEG2RAD * yaw) * cos(DEG2RAD * pitch),
	  sin(DEG2RAD * pitch),
	  sin(DEG2RAD * yaw) * cos(DEG2RAD * pitch) };

        cameraFront = Vector3Normalize(direction);
      
      } else { //
	EnableCursor();
	lastMousePos = GetMousePosition();
      }

      
      
      cameraPtr->target = cameraPtr->position + cameraFront;
    }
}


void CameraManager::resetCamera() 
{
  Vector3 pos = cameraPtr->position;
  Vector3 target = cameraPtr->target;
  Vector3 up = cameraPtr->up;
  delete cameraPtr;

  cameraPtr = new Camera { 0 };
  cameraPtr->position = pos;
  cameraPtr->target = target;
  cameraPtr->up = up;
  cameraPtr->fovy = 45.0f;                                
  cameraPtr->projection = CAMERA_PERSPECTIVE;
}


void CameraManager::setTarget(CelestialBody* body)
{
  resetCamera();
  
  // TODO: interpolate towards this
  float radius = body->getRadius();
  cameraPtr->target = body->getPosition();
  
  // TODO: interpolate towards this as well
  // TODO: Make the zoom a little better, perhaps make it something like the follows:
  cameraPtr->position = body->getPosition() + (Vector3) {radius*2, radius*2, radius*2};
  this->target = body;
  this->target->clickedTrue();
}

CameraManager& CameraManager::instance()
{
  static CameraManager* cm = new CameraManager();
  return *cm;
}

void CameraManager::unsetTarget()
{
  if(this->target) {
    resetCamera();

    this->target->clickedFalse();
    this->target = nullptr;
  }
}    

CameraManager::CameraManager()
  : target { nullptr }
{

  cameraPtr = new Camera;
  cameraPtr->position = (Vector3){ 0.0f, 0.0f, 0.0f }; 
  cameraPtr->target = (Vector3){ 0.0f, 0.0f, 0.0f };     
  cameraPtr->up = (Vector3){ 0.0f, 1.0f, 0.0f };          
  cameraPtr->fovy = 45.0f;                                
  cameraPtr->projection = CAMERA_PERSPECTIVE;
  
  SetCameraMode(*cameraPtr, CAMERA_CUSTOM);
}

CameraManager::~CameraManager()
{
  delete cameraPtr;
}
