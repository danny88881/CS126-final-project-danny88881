//
// Created by Danny on 11/15/2020.
//

#ifndef FINAL_PROJECT_INCLUDE_ACTOR_H_
#define FINAL_PROJECT_INCLUDE_ACTOR_H_

#include "cinder/gl/gl.h"

namespace final_project {

using glm::vec2;
using ci::geom::Rect;

class Actor {
 public:
  void update(double time_scale);
  void draw();

 private:
  vec2 position_;
  vec2 velocity_;
  Rect collision_;
  double max_health_;
  double health_;
};

}

#endif  // FINAL_PROJECT_INCLUDE_ACTOR_H_
