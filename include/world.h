//
// Created by Danny on 11/15/2020.
//

#ifndef FINAL_PROJECT_INCLUDE_WORLD_H_
#define FINAL_PROJECT_INCLUDE_WORLD_H_

#include "cinder/gl/gl.h"
#include <vector>
#include "actor.h"
#include "input_controller.h"

namespace final_project {

using glm::vec2;
using std::vector;
using std::map;

class World {
 public:
  World();

  void Setup();
  void Update(const InputController &controller);
  void Draw();

  int GetTextureIndex(const std::string &sprite_path) const;

  int LoadTexture(const std::string &sprite_path);

  static constexpr vec2 kWindowSize = vec2(512, 512);
 private:
  vector<Actor*> actors_;
  float time_scale_;
  ci::CameraOrtho camera_;
  map<std::string, std::pair<ci::gl::TextureRef, int>> texture_map_;
  const std::string kFloorSpritePath
      = "sprites/environment/Floor.png";
  ci::gl::BatchRef floor_rect_;
  ci::gl::GlslProgRef floor_material_;
};

}

#endif  // FINAL_PROJECT_INCLUDE_WORLD_H_
