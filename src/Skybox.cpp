#include <Skybox.hpp>

Skybox& Skybox::instance()
{
  static Skybox* skybox = new Skybox;
  return *skybox;
}

void Skybox::Draw()
{
  rlDisableBackfaceCulling();
  rlDisableDepthMask();
  DrawModel(model, Vector3Zero(), 1.0f, WHITE);
  rlEnableBackfaceCulling();
  rlEnableDepthMask();
}


Skybox::Skybox()
{
  model = LoadModelFromMesh(GenMeshCube(1.0f, 1.0f, 1.0f));

  model.materials[0].shader = LoadShader("res/shaders/skybox.vs", "res/shaders/skybox.fs");

  int envMap[1] = { MATERIAL_MAP_CUBEMAP };
  int zeroArr[1] = { 0 };
  SetShaderValue(model.materials[0].shader, GetShaderLocation(model.materials[0].shader, "environmentMap"), envMap, SHADER_UNIFORM_INT);
  SetShaderValue(model.materials[0].shader, GetShaderLocation(model.materials[0].shader, "doGamma"), zeroArr, SHADER_UNIFORM_INT);
  SetShaderValue(model.materials[0].shader, GetShaderLocation(model.materials[0].shader, "vflipped"), zeroArr, SHADER_UNIFORM_INT);

  //  Image img = LoadImage("res/textures/starbox/cubemaps_skybox.png");  
  //skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = LoadTextureCubemap(img, CUBEMAP_LAYOUT_AUTO_DETECT); 
  //UnloadImage(img);
  Image pvx = LoadImage("res/textures/starbox/xpos.png");
  Image nvx = LoadImage("res/textures/starbox/xneg.png");
  Image pvy = LoadImage("res/textures/starbox/ypos.png");
  Image nvy = LoadImage("res/textures/starbox/yneg.png");
  Image pvz = LoadImage("res/textures/starbox/zpos.png");
  Image nvz = LoadImage("res/textures/starbox/zneg.png");
  model.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = LoadTextureCubemap(pvx, nvx, pvy, nvy, pvz, nvz);

  UnloadImage(pvx);
  UnloadImage(pvy);
  UnloadImage(pvz);
  UnloadImage(nvx);
  UnloadImage(nvy);
  UnloadImage(nvz);
}


TextureCubemap Skybox::LoadTextureCubemap(Image pvx, Image nvx, Image pvy, Image nvy, Image pvz, Image nvz)
{
    TextureCubemap cubemap = { 0 };

    // TODO: checking to make sure the images are all "valid"?
    int size = pvx.width; // doesn't matter which one, eall of them should be the same
    Image faces = { 0 };

    // Convert image data to 6 faces in a vertical column, that's the optimum layout for loading
    faces = GenImageColor(size, size*6, MAGENTA);
    ImageFormat(&faces, pvx.format); // all ought to be in the same format!

    ImageDraw(&faces, pvx, (Rectangle) {0, 0, (float) size, (float) size}, (Rectangle){ 0, (float)size*0, (float)size, (float)size }, WHITE);
    ImageDraw(&faces, nvx, (Rectangle) {0, 0, (float) size, (float) size}, (Rectangle){ 0, (float)size*1, (float)size, (float)size }, WHITE);
    ImageDraw(&faces, pvy, (Rectangle) {0, 0, (float) size, (float) size}, (Rectangle){ 0, (float)size*2, (float)size, (float)size }, WHITE);
    ImageDraw(&faces, nvy, (Rectangle) {0, 0, (float) size, (float) size}, (Rectangle){ 0, (float)size*3, (float)size, (float)size }, WHITE);
    ImageDraw(&faces, pvz, (Rectangle) {0, 0, (float) size, (float) size}, (Rectangle){ 0, (float)size*4, (float)size, (float)size }, WHITE);
    ImageDraw(&faces, nvz, (Rectangle) {0, 0, (float) size, (float) size}, (Rectangle){ 0, (float)size*5, (float)size, (float)size }, WHITE);
  
  
    cubemap.id = rlLoadTextureCubemap(faces.data, size, faces.format);
    if (cubemap.id == 0) TRACELOG(LOG_WARNING, "IMAGE: Failed to load cubemap image");
  
    UnloadImage(faces);
  
    return cubemap;
  }
