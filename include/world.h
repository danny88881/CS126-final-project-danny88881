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
#include "user_interface.h"

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
  vector<Actor*> GetActors() const;
  void QueueFree(Actor* actor);
  Player* GetPlayer() const;

  static constexpr vec2 kWindowSize = vec2(512, 512);

  const vector<Attack*> player_attacks_ = {
      new Attack(Rect(-16, -64, 16, 48), 0, ActorType::kPlayer, 1.5f, 4,
                 "sprites/weapon/Spear.png", "sprites/ui/Spear.png",
                 3, 3, 3, 64, vec2(32, 64), {vec2(0, 3)}, true),
      new Attack(Rect(-64, -64, 64, 64), 0, ActorType::kPlayer, 0.6f, 7,
                 "sprites/weapon/Magic.png", "sprites/ui/Magic.png",
                 6, 3, 6, 84, vec2(64, 64), {vec2(3,5)}, false),
      new Attack(Rect(-16, -16, 16, 16), 12, ActorType::kPlayer, 2.0f, 2,
                 "sprites/weapon/Arrow.png", "sprites/ui/Arrow.png",
                 4, 2, 24, 24, vec2(16, 16), {vec2(0,100)}, true),
      new Attack()
  };
 private:
  Player* player_;
  vector<Actor*> actors_;
  vector<Actor*> removal_queue_;
  UserInterface ui_;
  float time_scale_;
  ci::CameraOrtho camera_;
  map<std::string, std::pair<ci::gl::TextureRef, int>> texture_map_;
  const std::string kFloorSpritePath
      = "sprites/environment/Floor.png";
  ci::gl::BatchRef floor_rect_;
  ci::gl::GlslProgRef floor_material_;
  const int kPlatformSize = 160;

  void RemoveActor(Actor* actor);
};

}

#endif  // FINAL_PROJECT_INCLUDE_WORLD_H_
