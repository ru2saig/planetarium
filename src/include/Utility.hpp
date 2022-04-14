/*
 * Utility: a simple header only library containing utility functions 
 */
#pragma once

#include <raylib.h>
#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include <cctype>


const int LINE_LENGTH_SMALL = 34; // witdh of box/width of font = 250/7.0
const int LINE_LENGTH_LARGE = 57;

namespace Utility {
  
  inline char* WrapText(const char* text, int lineLen)
  { 
    // return an malloced array of such wrapped text? or make a new buffer
    // and allocate memory as we go?
    char* str = (char*) malloc(1024 * sizeof(char)); // make sure to free! Perhaps wrap it in a string class? or use a string class?

    int i = 0;
    int idx = 0;
    int idx_last_space = -1; // index of last found space

  
    while(*text)
      {
	if(std::isspace(*text))
	  idx_last_space = idx;
	
	if(i == lineLen)
	  {
	    if(!std::isspace(*text))
	      {
		str[idx_last_space] = '\n';
		i = idx - idx_last_space; // start counting after the characters in the new line
	      }
	    else
	      { // does this even run?
		str[idx++] = '\n';
		i = 0;
	      }
	  }

	str[idx] = *text;

	idx++;
	text++;
	i++;
      }

    str[idx] = '\0';

    return str;
  }


  inline void DrawTextBox(int x, int y, int width, int height, const char* format...)
  {
    DrawRectangle(x, y, width, height, BLACK);
    DrawRectangleLines(x, y, width, height, WHITE);

    va_list args;
    va_start(args, format);
  
    char buf[1024];
    char* newbuf;
  
    vsprintf(buf, format, args);

    //newbuf = WrapText(buf, LINE_LENGTH_SMALL);
    DrawText(buf, x+4, y+4, 13, WHITE);

    //free(newbuf);
  
    va_end(args);  
  }
}
