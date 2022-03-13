#include <raylib.h>

int main(void)
{
  // Initialization
  // TODO: possible to do this automatically? fullscreen and stuff? resize?
  const int screenWidth = 800;
  const int screenHeight = 450;
    
  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

  SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

 
  Image image = LoadImage("res/planetarium.png");  // Load image data into CPU memory (RAM)
  Texture2D texture = LoadTextureFromImage(image);       // Image converted to texture, GPU memory (RAM -> VRAM)
  UnloadImage(image);                                    // Unload image data from CPU memory (RAM)

  //image = LoadImageFromTexture(texture);                 // Load image from GPU texture (VRAM -> RAM)
  //UnloadTexture(texture);                                // Unload texture from GPU memory (VRAM)

  //texture = LoadTextureFromImage(image);                 // Recreate texture from retrieved image data (RAM -> VRAM)
  // UnloadImage(image);                    
    
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
      DrawTexture(texture, screenWidth/2 - texture.width/2, screenHeight/2 - texture.height/2, WHITE);

     

      EndDrawing();
      //----------------------------------------------------------------------------------
    }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow();        // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}
