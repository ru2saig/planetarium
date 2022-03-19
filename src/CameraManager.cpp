#include "raylib.h"
#include <CameraManager.hpp>
#include <rcamera.h>
#include <PVector3.hpp>
#include <CelestialBody.hpp>
#include <iostream>
using namespace VMath;

void CameraManager::Update()//Camera *camera)
{
  if(target) // follow target
    {
      float r = target->getRadius();
      cameraPtr->target = target->getPosition();
      cameraPtr->position = target->getPosition() + (Vector3) {r*2, r*2, r*2};
    }
  
  UpdateCamera(cameraPtr);
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


void CameraManager::setTarget(CelestialBody *body)
{
  resetCamera();
  SetCameraMode(*cameraPtr, CAMERA_CUSTOM);
  // TODO: interpolate towards this
  cameraPtr->target = body->getPosition();
  // TODO: interpolate towards this as well
  // TODO: Make the zoom a little better, perhaps make it something like the follows:
  cameraPtr->position = body->getPosition() + (Vector3) {20.0, 20.0, 20.0};
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
    SetCameraMode(*cameraPtr, CAMERA_FREE);
    this->target->clickedFalse();
    this->target = nullptr;
  }
}    

CameraManager::CameraManager() //(Camera *camera)
  : target { nullptr }
{
  cameraPtr = new Camera;
  cameraPtr->position = (Vector3){ 0.0f, 100.0f, 0.0f }; 
  cameraPtr->target = (Vector3){ 0.0f, 10.0f, 0.0f };     
  cameraPtr->up = (Vector3){ 0.0f, 1.0f, 0.0f };          
  cameraPtr->fovy = 45.0f;                                
  cameraPtr->projection = CAMERA_PERSPECTIVE;
  
  SetCameraMode(*cameraPtr, CAMERA_FREE);
}

CameraManager::~CameraManager()
{
  delete cameraPtr;
}
