//
// Created by Danny on 11/15/2020.
//

#include "cinder/Rect.h"
#include "actor.h"

namespace final_project {

Actor::Actor() : position_(0,0), velocity_(0,0), max_health_(3),
      health_(max_health_), speed_(10), hit_box_(-10, -10, 10, 10) {
}

void Actor::Update(float time_scale, const vector<Actor*> &actors,
            const InputController &controller) {
  position_ += velocity_ * vec2(time_scale);
}

void Actor::Draw() const {
}

bool Actor::IsColliding(const Actor &other_actor) {
  if ((collision_.x1_ + position_.x
       > other_actor.collision_.x2_ + other_actor.position_.x)
      ||(collision_.x2_ + position_.x
          < other_actor.collision_.x1_ + other_actor.position_.x)
      ||(collision_.y1_ + position_.y
          > other_actor.collision_.y2_ + other_actor.position_.y)
      ||(collision_.y2_ + position_.y
          < other_actor.collision_.y1_ + other_actor.position_.y) )
    return false;
  else
    return true;
}

}