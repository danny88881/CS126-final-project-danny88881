//
// Created by Danny on 12/7/2020.
//

#ifndef FINAL_PROJECT_INCLUDE_ACTORS_SPAWN_POSITION_H_
#define FINAL_PROJECT_INCLUDE_ACTORS_SPAWN_POSITION_H_

#include "actors/enemy.h"

namespace final_project {

class SpawnPosition : public Enemy {
 public:
  SpawnPosition(vec2 position);

  virtual void Update(float time_scale, World &world,
                      const InputController &controller) override;
 private:
  int kSpawnDelay = 160;
  int current_frame_;
};

}

#endif  // FINAL_PROJECT_INCLUDE_ACTORS_SPAWN_POSITION_H_
