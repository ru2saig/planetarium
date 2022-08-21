#ifndef _SKYBOX_HPP_
#define _SKYBOX_HPP_
#include <raylib.h>
#include <rlgl.h>
#include <raymath.h>


class Skybox
{
private:
  Skybox();
  Model model;
public:
  // loads a cubemap from 6 images: +X, -X, +Y, -Y, +Z, -Z
  static TextureCubemap LoadTextureCubemap(Image pvx, Image nvx, Image pvy, Image nvy, Image pvz, Image nvz);
  static Skybox& instance();
  ~Skybox() { UnloadModel(model); }
  void Draw();
};


#endif /* _SKYBOX_HPP_ */
