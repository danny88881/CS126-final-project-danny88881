//
// Created by Danny on 11/15/2020.
//

#ifndef FINAL_PROJECT_INCLUDE_WORLD_H_
#define FINAL_PROJECT_INCLUDE_WORLD_H_

#include "cinder/gl/gl.h"
#include <vector>
#include "actor.h"
#include "attack.h"
#include "input_controller.h"

namespace final_project {

using glm::vec2;
using std::vector;
using std::map;

class World {
 public:
  /**
   * Creates a world with a player and boundaries
   */
  World();

  void Setup();
  void Update(const InputController &controller);
  void Draw();

  int GetTextureIndex(const std::string &sprite_path) const;

  int LoadTexture(const std::string &sprite_path);

  void AddActor(Actor* actor);
  void RemoveActor(Actor* actor);
  void QueueRemoval(Actor* actor);
  vector<Actor*> GetActors() const;

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
  const vector<Attack*> player_attacks_ = {
      new Attack(),
      new Attack(),
      new Attack(),
      new Attack()
  };
};

}

#endif  // FINAL_PROJECT_INCLUDE_WORLD_H_
