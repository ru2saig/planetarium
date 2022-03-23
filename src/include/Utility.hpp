/*
 * Utility: a simple header only library containing customized text drawing function
 */
#pragma once
#include <raylib.h>
#include <cstdio>
#include <cstdarg>
#include <cstdlib>
#include <stdio.h>

const int LINE_LENGTH_SMALL = 34; // witdh of box/width of font = 250/7.0
const int LINE_LENGTH_LARGE = 57;

char* WrapText(const char* text, int lineLen)
{
  // return an malloced array of such wrapped text? or make a new buffer
  // and allocate memory as we go?
  char* str = (char*) malloc(512 * sizeof(char));

  int i = 0;
  int idx = 0;
  while(*text)
  {
    if(i == lineLen)
      {
	str[idx++] = '\n';
	i = 0;
      }

    str[idx] = *text;
    
    idx++;
    text++;
    i++;
  }

  str[idx] = '\0';

  return str;
}


void DrawTextBox(int x, int y, int width, int height, const char* format...)
{
  DrawRectangle(x, y, width, height, BLACK);
  DrawRectangleLines(x, y, width, height, WHITE);

  // TextFormat? send it to that?
  va_list args;
  va_start(args, format);
  
  const char* buf;
  vprintf(format, args);
  
  // get the formated strings into buf

  //DrawText(buf, x+4, y+4, 13, WHITE);
  
  va_end(args);  
}
