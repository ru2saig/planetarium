#ifndef _GUIUTIL_HPP_
#define _GUIUTIL_HPP_

#include <raygui.hpp>
#include <raylib.h>
#include <string>


static int *CodepointRemoveDuplicates(int*, int, int*);


class GlobalFonts
{
private:
  Font tel;
  Font hi;
  Font eng;
  int currentLang;
  
  GlobalFonts();
public:
  int returnCurrentLang() { return currentLang; }
  Font returnCurrentFont()
  {
    switch(currentLang)
      {
	case 0:
	  return tel;
	  break;

      case 1:
	return hi;
	break;

      case 2:
	return eng;
	break;
	
      }

    return GetFontDefault();
  }
  
  static GlobalFonts& GlobalFontInstance();
  Font getTelugu() { return tel; }
  Font getHindi() { return hi; }
  Font getEng() { return eng; }
};


class RGuiControl
{
protected:
  int id;
  std::string text;
  Rectangle bounds;
public:
  RGuiControl(int id_, float x, float y, float width, float height, std::string _text)
    : id { id_ },
      bounds { .x=x, .y=y, .width=width, .height=height },
      text { _text }
  {}

  virtual void DrawControl() = 0;
};


class RGuiListView : public RGuiControl
{
protected:
  int listViewActive;
  int listViewScrollIndex;
public:
  RGuiListView(int id, float x, float y, float width, float height, std::string text)
    : RGuiControl(id, x, y, width, height, text),
      listViewActive { -1 },
      listViewScrollIndex { 0 }
  {}
  
  void DrawControl()
  {
    listViewActive = GuiListView(bounds, text.c_str(), &listViewScrollIndex, listViewActive);
  }
};                         



#endif /* _GUIUTIL_HPP_ */
