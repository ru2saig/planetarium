#ifndef _NAVIGATION_HPP_
#define _NAVIGATION_HPP_

#include <GUIUtil.hpp>
#include <raygui.hpp>
#include <raylib.h>
#include <string>

class planetNavigationList : public RGuiControl
{
private:
  int currentPlanetActive;
  int currentPlanet;
  int oldPlanetActive;
  Rectangle scrollLabel;
public:
  planetNavigationList()
    : RGuiControl(0, 0, 20, GetScreenWidth()/8.0f, GetScreenHeight(), "FREE ROAM;MERCURY;VENUS;EARTH;MARS;JUPITER;SATURN;URANUS;NEPTUNE"),
      currentPlanetActive { 3 },
      oldPlanetActive { -1 },
      currentPlanet { 0 },
      scrollLabel { 0, 0, GetScreenWidth()/2.0f, 24 }
  {}

  void DrawControl()
  {
    GuiSetFont(GetFontDefault());
    currentPlanetActive = GuiListView(bounds, text.c_str(), &currentPlanet, currentPlanetActive);

    if(currentPlanetActive == oldPlanetActive)
      oldPlanetActive = currentPlanetActive;
    
    GuiLabel(scrollLabel, "NAVIGATION: ");
  }

  int getOption()
  {
    return currentPlanetActive;
  }

  void setFreeRoam()
  {
    currentPlanetActive = 0;
  }
  
  bool changedOption()
  {
    return oldPlanetActive != currentPlanetActive;
  }
};                          


#endif /* _NAVIGATION_HPP_ */
