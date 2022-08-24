/*************************************************************
 * CameraManager - singleton (for now) class that manages a custom camera tailerd fordward
                   planetarium

 * Features -
 * Methods
*************************************************************/
#pragma once
#include <raylib.h>
#include <PVector3.hpp>
#include <CelestialBody.hpp>
#include <memory>


class CameraManager
{
public:
  static CameraManager& instance();  
  void Update();
  Camera getCamera() { return *cameraPtr; }
  Camera* getCameraPtr() { return cameraPtr; }
  void resetCamera();
  void setTarget(CelestialBody*); // sets target to follow
  void unsetTarget(); // sets target to nullptr
  ~CameraManager();
  
private:
  CameraManager();
  CelestialBody* target;
  Camera* cameraPtr;
  
};   
