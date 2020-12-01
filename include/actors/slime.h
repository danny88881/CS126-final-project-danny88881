//
// Created by Danny on 11/30/2020.
//

#ifndef FINAL_PROJECT_SRC_ACTORS_SLIME_H_
#define FINAL_PROJECT_SRC_ACTORS_SLIME_H_

#include "actors/enemy.h"

namespace final_project {

class Slime : public Enemy {
 public:
  Slime(vec2 position);

  virtual void Update(float time_scale, World &world,
                      const InputController &controller) override;
 private:
  int kDamage = 1;
  int kKnockbackForce = 3;
};

}

#endif  // FINAL_PROJECT_SRC_ACTORS_SLIME_H_
