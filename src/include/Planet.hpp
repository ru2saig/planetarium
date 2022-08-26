#pragma once
#include <raylib.h>
#include <Orbit.hpp>
#include <CelestialBody.hpp>
#include <Utility.hpp>
typedef char cstring[256]; // TODO: make the information thing more optimized for space
typedef const char* string;

#define FLT_MAX     340282346638528859811704183484516925440.0f     // Maximum value of a float, from bit pattern 01111111011111111111111111111111


class Planet : public CelestialBody
{
public:
  Planet() = default;
  Planet(string, string, std::string, Vector3, float, float);
  virtual ~Planet();
  
  void Draw() override;
  void Update() override;
  void Update(Camera*);
  void DisplayInfo() override;
  void CheckPointer(Ray);
  
  bool getClicked() { return clicked; }
  float getRadius() { return radius; }
  
  static void toggleShowOrbit() { Planet::showOrbit = !Planet::showOrbit; }
  static void toggleShowHitBox() { Planet::showHitBox = !Planet::showHitBox; }
  
protected:
  static float BASE_PLANET_RADIUS;
  static bool showOrbit;
  static bool showHitBox;

  Model model;
  Shader shader;
  
  Orbit orbit;
  RayCollision planetEntered; // when pointer enters box

  // general info
  cstring planetName;
  char*  planetInfo;
  
  // detailed info
  cstring mass; // 10^24 kg
  cstring volume; // 10^10 km^3
  cstring gravity; // m/s^2
  cstring escape_velocity; // km/s
  cstring no_of_natural_satellites; 
  cstring moment_of_inertia; // I/MR^2
  cstring diamteter; // km
  cstring perihelion; // 10^6 km
  cstring aphelion; // 10^6 km
  cstring length_of_day; // hours
  cstring avg_temp; // Celsius
  cstring orbital_period; // days
  cstring orbital_vel; // km/s
  cstring mean_orbital_vel; // km/s

};

