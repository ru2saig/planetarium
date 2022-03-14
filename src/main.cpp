#include <raylib.h>
#include <Vector3.hpp>



int main(void)
{
  // Initialization
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
  InitWindow(GetScreenWidth(), GetScreenHeight(), "Planetarium");
  
  SetTargetFPS(60);               // target 60 fps
 
  Image image = LoadImage("res/planetarium.png");  // Load image data into CPU memory (RAM)
  Texture2D texture = LoadTextureFromImage(image);       // Image converted to texture, GPU memory (RAM -> VRAM)
  UnloadImage(image);                                    // Unload image data from CPU memory (RAM)

  //image = LoadImageFromTexture(texture);                 // Load image from GPU texture (VRAM -> RAM)
  //UnloadTexture(texture);                                // Unload texture from GPU memory (VRAM)

  //texture = LoadTextureFromImage(image);                 // Recreate texture from retrieved image data (RAM -> VRAM)
  // UnloadImage(image);                    


  VMath::Vector3 v1{ 10.0, 10.0, 10.0 };
  VMath::Vector3 v2{ 10.0, 10.0, 10.0 };
  VMath::Vector3 v3 = v1 + v2;
  
  // Main game loop
  while (!WindowShouldClose())    // Detect window close button or ESC key
    {
      // Update
      //----------------------------------------------------------------------------------
      // TODO: Update your variables here
      //----------------------------------------------------------------------------------

      // Draw
      //----------------------------------------------------------------------------------
      BeginDrawing();

      ClearBackground(RAYWHITE);
      DrawTexture(texture, GetScreenWidth()/2 - texture.width/2, GetScreenHeight()/2 - texture.height/2, WHITE);

     

      EndDrawing();
      //----------------------------------------------------------------------------------
    }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow();        // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
