#include <raylib.h>
#include <PVector3.hpp>


int main(void)
{
  // Initialization
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
  InitWindow(GetScreenWidth(), GetScreenHeight(), "Planetarium");

  Camera camera = { 0 };
  camera.position = (Vector3){ 100.0f, 100.0f, 100.0f }; // Camera position
  camera.target = (Vector3){ 0.0f, 10.0f, 0.0f };     // Camera looking at point
  camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;                                // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type

  // load models
  Model earth_model = LoadModel("res/earth/earth.obj"); //LoadModelFromMesh(GenMeshSphere(32, 64, 64)); //LoadModel("res/earth/earth.obj");
  Texture2D earth_texture = LoadTexture("res/earth/earth_albedo.png");
  earth_model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = earth_texture;
  VMath::PVector3 earth_pos {0.0, 0.0, 0.0};


  SetCameraMode(camera, CAMERA_FREE);
  SetTargetFPS(60);               // target 60 fps

  // Main game loop
  while (!WindowShouldClose())    // Detect window close button or ESC key
    {
      // Update
      UpdateCamera(&camera);

      
      // Draw
      BeginDrawing();
      BeginMode3D(camera);

      ClearBackground(BLACK);
      DrawModel(earth_model, earth_pos.vec3, 1.0f, WHITE);
      
      
      EndMode3D();
      EndDrawing();
  
    }

  // De-Initialization
  UnloadTexture(earth_texture);
  UnloadModel(earth_model);
  CloseWindow();        // Close window and OpenGL context


  return 0;
}
