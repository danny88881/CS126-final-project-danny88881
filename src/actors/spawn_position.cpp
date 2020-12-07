//
// Created by Danny on 12/7/2020.
//

#include "actors/spawn_position.h"
#include "actors/slime.h"
#include "world.h"

namespace final_project {

SpawnPosition::SpawnPosition(vec2 position) : Enemy("sprites/enemies/spawn.png", 1, 16, position,
vec2(0), Rect(0,0,0,0), Rect(0,0,0,0), 10000, 10000, 0,
glm::vec4(1)), current_frame_(0) {

}

void SpawnPosition::Update(float time_scale, World &world,
                   const InputController &controller) {
  ++current_frame_;
  if (current_frame_ > kSpawnDelay) {
    world.QueueFree(this);
    auto enemy = new Slime(position_);
    world.AddActor(enemy);
  }
}

}