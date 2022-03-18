/*************************************************************
 * PCamera - an implentation tailerd for planetarium
 *           Is a singleton class for now.
 * Uses rcamera, from raylib with custom methods and variables
 * Functions of Interest -
 * Features -
*************************************************************/
#pragma once
#include <rcamera.h>
#include <PVector3.hpp>
#include <CelestialBody.hpp>

enum class CameraModes {
  FREE_ROAM = 0, // point and click roam the universe
  TOUR, // tour mode, follow the path
};

class PCamera {
public:
  static PCamera* instance();

  void Update();
  void SetTarget(CelestialBody*);
  void FollowPath(Vector3*); // interpolate through a path, given by an array of Vector3

  Camera* getCamera() { return &camera; }
  
private:
  PCamera();

  Camera camera;
  CelestialBody* target;
  CameraModes camera_mode;
};
