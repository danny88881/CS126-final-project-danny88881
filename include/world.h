//
// Created by Danny on 11/15/2020.
//

#ifndef FINAL_PROJECT_INCLUDE_WORLD_H_
#define FINAL_PROJECT_INCLUDE_WORLD_H_

#include <vector>

#include "actor.h"
#include "actors/player.h"
#include "attack.h"
#include "cinder/gl/gl.h"
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
  ~World();

  void Setup();
  void Update(const InputController &controller);
  void Draw();

  void StartGame();

  /**
   * Gets the index that the spirte is bound to
   * @param sprite_path the path of the sprite
   * @return the index that the sprite is bound to
   */
  int GetTextureIndex(const std::string &sprite_path) const;

  /**
   * Loads a texture into the current texture map
   * @param sprite_path the path of the texture to load
   * @return the int that the texture is bound to
   */
  int LoadTexture(const std::string &sprite_path);

  /**
   * Spawns an actor into the world
   * @param actor the pointer of the actor to spawn
   */
  void AddActor(Actor* actor);
  vector<Actor*> GetActors() const;

  /**
   * Queues the passed actor for destruction on the next update tick
   * @param actor the actor to be destroyed
   */
  void QueueFree(Actor* actor);

  Player* GetPlayer() const;

  int GetPoints() const;

  void AddPoint();

  static constexpr vec2 kWindowSize = vec2(512, 512);

  const vector<Attack*> kPlayerAttacks = {
      new Attack(Rect(-24, -96, 24, 64), 0, ActorType::kPlayer, 1.5f, 7,
                 "sprites/weapon/Spear.png", "sprites/ui/Spear.png",
                 3, 3, 3, 64, vec2(32, 64), {vec2(0, 3)}, true),
      new Attack(Rect(-32, -256, 32, 256), 0, ActorType::kPlayer, 100.0f, 0,
                 "sprites/weapon/Laser.png", "sprites/ui/Laser.png",
                 6, 2, 6, 256, vec2(32, 256), {vec2(3, 6)}, true),
      new Attack(Rect(-96, -96, 96, 96), 0, ActorType::kPlayer, 0.6f, 10,
                 "sprites/weapon/Magic.png", "sprites/ui/Magic.png",
                 6, 3, 6, 84, vec2(64, 64), {vec2(3,5)}, false),
      new Attack(Rect(-24, -24, 24, 24), 12, ActorType::kPlayer, 2.0f, 5,
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
  double last_spawn_time_;
  double spawn_interval_;
  const double kMinSpawnInterval = (time_t)0.5;
  const int kPlatformSize = 160;
  const int kSpawnAreaSize = 100;
  int points_;

  void RemoveActor(Actor* actor);
};

}

#endif  // FINAL_PROJECT_INCLUDE_WORLD_H_
