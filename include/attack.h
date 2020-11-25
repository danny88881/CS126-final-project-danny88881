//
// Created by Danny on 11/25/2020.
//

#ifndef FINAL_PROJECT_INCLUDE_ATTACK_H_
#define FINAL_PROJECT_INCLUDE_ATTACK_H_

#include "actor.h"

namespace final_project {

class World;

enum AttackDirection {
  kUpAttack,
  kDownAttack,
  kLeftAttack,
  kRightAttack,
  kNone
};

class Attack : public Actor {
 public:
  Attack();
  Attack(AttackDirection direction);

  virtual void Setup(World &world) override;

  virtual void Update(float time_scale, const World &world,
                      const InputController &controller) override;
  virtual void Draw() const override;
 protected:
  Attack(float damage, std::string sprite_sheet_path,
         int max_frames, int frame_life);
  AttackDirection direction_;
  float damage_;
  std::string sprite_sheet_path_
      = "sprites/weapon/32slash.png";
  ci::gl::BatchRef rect_;
  ci::gl::GlslProgRef material_;
  int frame_skip_ = 10;
  int max_frames_ = 4;
  int frame_index_;
  int frame_life_;
};

}

#endif  // FINAL_PROJECT_INCLUDE_ATTACK_H_
