#include <Window.hpp>
#include <raylib.h>

// TODO: Add a window icon
// TODO: Manage application states, here? or in main.cpp? How to do that?
// TODO: How to make sure that those utility functions (defined in the header, work?)

Window::Window() {
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
  InitWindow(GetScreenWidth(), GetScreenHeight(), "Planetarium");
}

Window::~Window() {
  CloseWindow();        // Close window and OpenGL context
}

