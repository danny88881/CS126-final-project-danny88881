//
// Created by Danny on 11/15/2020.
//

#ifndef FINAL_PROJECT_INCLUDE_ACTORS_PLAYER_H_
#define FINAL_PROJECT_INCLUDE_ACTORS_PLAYER_H_

#include "cinder/app/App.h"
#include "actor.h"
#include "attack.h"

namespace final_project {

class World;

class Player : public Actor {
 public:
  Player();
  Player(vec2 position);

  ~Player();

  virtual void Setup(World &world) override;

  virtual void Update(float time_scale, World &world,
                      const InputController &controller) override;
  virtual void Draw() const override;

  vector<Attack*> GetAttacks() const;
 private:
  const std::string kSpriteSheetPath
      = "sprites/player/CharacterSpriteSheet.png";
  const std::string kScytheSpritePath
      = "sprites/weapon/Scythe.png";
  ci::gl::BatchRef rect_;
  ci::gl::BatchRef scythe_rect_;
  ci::gl::GlslProgRef material_;
  ci::gl::GlslProgRef scythe_material_;
  const int kMaxFrames = 4;
  const int kFrameSkip = 8;
  int frame_index_;
  int x_scale_;

  AttackDirection attack_direction_;
  bool can_attack_;
  int attack_frame_;
  int attack_frame_length_;
  int attack_frame_delay_;

  vector<Attack*> attacks_;

  void AttackAtDirection(AttackDirection attack_direction, World &world);
};

}

#endif  // FINAL_PROJECT_INCLUDE_ACTORS_PLAYER_H_
