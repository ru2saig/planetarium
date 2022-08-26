#ifndef _GUIUTIL_HPP_
#define _GUIUTIL_HPP_

#include <raygui.hpp>
#include <raylib.h>
#include <string>


static int *CodepointRemoveDuplicates(int*, int, int*);
void DrawTextBoxed(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint);   // Draw text using font inside rectangle limits
void DrawTextBoxedSelectable(Font font, const char *text, Rectangle rec, float fontSize, float spacing, bool wordWrap, Color tint, int selectStart, int selectLength, Color selectTint, Color selectBackTint);    // Draw text using font inside rectangle limits with support for text selection


enum Lang
{
  ENGLISH = 0,
  TELUGU,
  HINDI,
  MARATHI,
};


class GlobalFonts
{
private:
  Font tel;
  Font hi;
  Font eng;
  int size = 0;
  int fontSize = 0;
  int fontSpacing = 0;
  int currentLang;
  
  GlobalFonts();
public:
  int returnCurrentLang() { return currentLang; }
  Font returnCurrentFont()
  {
    switch(currentLang)
      {
      case Lang::TELUGU:
	  return tel;
	  break;

      case Lang::ENGLISH:
	return eng;
	break;

      case Lang::HINDI:
	return hi;
	break;
	
      }

    return GetFontDefault();
  }
  
  static GlobalFonts& GlobalFontInstance();
  Font getTelugu() { return tel; }
  Font getHindi() { return hi; }
  Font getEng() { return eng; }
  int getSize() { return size; }
  int getFontSize() { return fontSize; }
  int getFontSpacing() { return fontSpacing; }
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


class RGuiTextBoxMulti : public RGuiControl
{
private:
  bool editMode;
  char* mText;

public:
  RGuiTextBoxMulti(int id_, float x, float y, float width, float height, std::string _text)
    : RGuiControl(id_, x, y, width, height, _text),
      editMode { false }
  {
    mText = (char*) malloc(sizeof(char) * text.size());
    
    for(int i = 0; i < text.size(); i++)
        mText[i] = text[i];
  }

  void DrawControl() override
  {
    if (GuiTextBoxMulti(bounds, mText, text.size(), editMode))
      editMode = !editMode;
  }

  ~RGuiTextBoxMulti()
  {
    free(mText);
  }

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
