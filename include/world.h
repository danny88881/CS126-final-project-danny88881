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

class World {
 public:
  World();

  void Update(const InputController &controller);
  void Draw();

  static constexpr vec2 kWindowSize = vec2(800, 800);
 private:
  vector<Actor*> actors_;
  float time_scale_;
};

}

#endif  // FINAL_PROJECT_INCLUDE_WORLD_H_
