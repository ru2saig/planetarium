#include <PCamera.hpp>
#include <rcamera.h>
#include <PVector3.hpp>
#include <CelestialBody.hpp>
#include <iostream>
using namespace VMath;

PCamera* PCamera::instance()
{
  static PCamera *pCamera = new PCamera;
  return pCamera;
}

PCamera::PCamera()
  : target { nullptr }, camera_mode { CameraModes::FREE_ROAM }
{
    camera.position = (Vector3){ 100.0f, 100.0f, 100.0f }; // PCamera position
    camera.target = (Vector3){ 0.0f, 10.0f, 0.0f };     // PCamera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // PCamera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // PCamera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                   // PCamera mode type
    SetCameraMode(camera, CAMERA_CUSTOM);
}

void PCamera::Update() 
{
  // TODO: add a custom update function, as camera is in CAMERA_CUSTOM mode
  // TOOD: wonder if changing modes when there is no target will work?
  UpdateCamera(&(this->camera));
}

void PCamera::SetTarget(CelestialBody *body)
{
  // TODO: interpolate towards this
  this->camera.target = body->getPosition();
  // TODO: interpolate towards this as well
  // TODO: Make the zoom a little better, perhaps make it something like the follows:
  this->camera.position = body->getPosition() + (Vector3) {20.0, 20.0, 20.0};
}


