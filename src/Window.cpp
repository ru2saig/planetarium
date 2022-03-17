#include <Window.hpp>
#include <raylib.h>

Window::Window() {
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
  InitWindow(GetScreenWidth(), GetScreenHeight(), "Planetarium");
}

Window::~Window() {
  CloseWindow();        // Close window and OpenGL context
}

