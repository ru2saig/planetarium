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
  
  if(target) // follow target
    {
      float r = target->getRadius();
      cameraPtr->target = target->getPosition();
      cameraPtr->position = target->getPosition() + (Vector3) {100, 100, 100};
    }

  UpdateCamera(cameraPtr);
}


void CameraManager::resetCamera() 
{
  Vector3 pos = cameraPtr->position;
  Vector3 target = cameraPtr->target;
  Vector3 up = cameraPtr->up;
  delete cameraPtr;

  SetCameraMode(this->getCamera(), CAMERA_FREE);

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
  SetCameraMode(this->getCamera(), CAMERA_CUSTOM);
  
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

    SetCameraMode(this->getCamera(), CAMERA_FREE);
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
  
  SetCameraMode(*cameraPtr, CAMERA_FREE);
}

CameraManager::~CameraManager()
{
  delete cameraPtr;
}
