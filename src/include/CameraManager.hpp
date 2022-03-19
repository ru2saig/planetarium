/*************************************************************
 * CameraManager - singleton (for now) class that manages a custom camera tailerd fordward
                   planetarium
 * Uses rcamera, from raylib with custom methods and variables
 * Features -
 * Methods
*************************************************************/
#pragma once
#include <rcamera.h>
#include <PVector3.hpp>
#include <CelestialBody.hpp>



enum class CameraModes {
  FREE_ROAM = 0, // point and click roam the universe
  TOUR, // tour mode, follow the path
};

class CameraManager
{
public:
  static CameraManager& instance();  
  void Update();
  Camera getCamera() { return *cameraPtr; }
  void resetCamera();
  void setTarget(CelestialBody*); // sets target to follow
  void unsetTarget(); // sets target to nullptr
  ~CameraManager();
  
private:
  CameraManager();
  CelestialBody* target;
  Camera* cameraPtr;
};   
