//
// Created by Danny on 11/25/2020.
//

#ifndef FINAL_PROJECT_INCLUDE_ATTACK_H_
#define FINAL_PROJECT_INCLUDE_ATTACK_H_

#include "actor.h"

namespace final_project {

class World;

enum AttackDirection {
  kUpAttack = 0,
  kDownAttack,
  kLeftAttack,
  kRightAttack,
  kNone
};

class Attack : public Actor {
 public:
  Attack();
  Attack(const Attack &attack, double rotation, vec2 position);

  virtual void Setup(World &world) override;

  virtual void Update(float time_scale, World &world,
                      const InputController &controller) override;
  virtual void Draw() const override;
 protected:
  double rotation_;
  float damage_;
  std::string sprite_sheet_path_
      = "sprites/weapon/32slash.png";
  ci::gl::BatchRef rect_;
  ci::gl::GlslProgRef material_;
  int max_frames_ = 4;
  int frame_index_;
  float frame_life_;
  vector<Actor*> hit_actors_;
};

}

#endif  // FINAL_PROJECT_INCLUDE_ATTACK_H_
