//
// Created by Danny on 11/15/2020.
//

#include "actor.h"

void final_project::Actor::update(double time_scale) {
  position_ += velocity_ * vec2(time_scale);
}

void final_project::Actor::draw() {

}
