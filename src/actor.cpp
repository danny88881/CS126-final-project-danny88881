//
// Created by Danny on 11/15/2020.
//

#include "actor.h"

namespace final_project {

Actor::Actor() {
}

void Actor::Update(float time_scale, const World &world) {
  position_ += velocity_ * vec2(time_scale);
}

void Actor::Draw() const {
}

bool Actor::IsColliding(const Actor &other_actor) {
  // not sure why intersects() is not working
  if( ( collision_.x1 > other_actor.collision_.x2 )
      || ( collision_.x2 < other_actor.collision_.x1 )
      || ( collision_.y1 > other_actor.collision_.y2 )
      || ( collision_.y2 < other_actor.collision_.y1 ) )
    return false;
  else
    return true;
}

}