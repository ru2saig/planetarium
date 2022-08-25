#pragma once

#include "raylib.h"
struct Window
{
  Window();
  ~Window();
  int getScreenWidth() { return GetScreenWidth(); }
  int getScreenHeight() { return GetScreenHeight(); }
  int getScreenHalfWidth() { return GetScreenWidth()/2; }
  int getScreenHalfHeight() { return GetScreenHeight()/2; }
};
